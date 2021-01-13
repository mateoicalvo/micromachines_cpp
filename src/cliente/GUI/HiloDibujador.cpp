#include "includes/cliente/GUI/HiloDibujador.h"

#include "includes/cliente/GUI/escenas/EscenaMenu.h"

#include "includes/cliente/utils/ConfigCliente.h"

#include <SDL2/SDL.h>
#include <includes/common/Cronometro.h>
#include <iostream>

void HiloDibujador::step(uint32_t iteracion, Escena &escena) {
  bool obtenido = false;
  std::shared_ptr<Evento> evento;
  while ((obtenido = eventos_.get(evento))) {
    // ACA SE PROCESAN LOS EVENTOS
    evento.get()->actualizar((Handler &) escena);
  }
  if (grabador_.estaCorriendo()) {
    renderizador_.dibujar(iteracion, escena, grabador_.getBuffer());
  } else {
    renderizador_.dibujar(iteracion, escena);
  }
}

HiloDibujador::HiloDibujador(Ventana &ventana,
                             Renderizador &renderizador,
                             HiloGrabador &grabador,
                             ColaProtegida<std::shared_ptr<EventoGUI>> &eventosGUI,
                             ColaBloqueante<std::shared_ptr<Evento>> &eventosAEnviar_,
                             bool &seguirCorriendo)
    :
    ventana_(ventana),
    renderizador_(renderizador),
    grabador_(grabador),
    eventosGUI_(eventosGUI),
    eventosAEnviar_(eventosAEnviar_),
    musicaAmbiente(CONFIG_CLIENTE.musicaAmbiente(), true),
    seguirCorriendoCliente(seguirCorriendo) {
  escenas_.emplace(std::make_shared<EscenaMenu>(renderizador_,
                                                eventosGUI_,
                                                escenas_,
                                                eventosAEnviar_,
                                                musicaAmbiente,
                                                seguirCorriendoCliente));
}

void HiloDibujador::correr() {
  double frecuencia = (double) 1 / (double) CONFIG_CLIENTE.fps();
  frecuencia *= 1000;
  Cronometro c;
  double t1 = c.ahora();
  //TODO: Resetear cada vez que se cambia de escena
  uint32_t iteracion = 0;
  while (seguirCorriendo_) {
    Escena &escenaActual = *escenas_.top().get();
    step(iteracion, escenaActual);
    //FIXME: Se arregla haciendo que el metodo manejar evento devuelva true si hay que continuar.
    // También se puede chequear al hacer pop que no se esté quedando sin escenas
    bool obtenido = false;
    std::shared_ptr<EventoGUI> evento;
    while ((obtenido = eventosGUI_.get(evento))) {
      escenaActual.manejarInput(*evento.get());
    }
    double t2 = c.ahora();
    double resto = frecuencia - (t2 - t1);
    if (resto < 0) {
      double atraso = -resto;
      double perdidos = atraso - std::fmod(atraso, frecuencia);
      resto = frecuencia - std::fmod(atraso, frecuencia);
      t1 += perdidos;
      iteracion += std::floor(perdidos / frecuencia);
    }
    dormir(resto);
    t1 += frecuencia;
    iteracion += 1;

  }
}

void HiloDibujador::detener() {
  seguirCorriendo_ = false;
}

ColaProtegida<std::shared_ptr<Evento>> &HiloDibujador::eventosEntrantes() {
  return eventos_;
}
