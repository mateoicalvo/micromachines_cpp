#include <includes/cliente/GUI/AnimacionFactory.h>
#include <includes/cliente/utils/ConfigCliente.h>
#include "includes/cliente/GUI/escenas/EscenaPodio.h"

void EscenaPodio::dibujarAutos(int nroIteracion) {
  for (auto &kv: this->mapaAutos) {
    kv.second.get()->getSonido().setVolume(0);
    Animacion &animacion = kv.second.get()->getAnimacion();
    Area areaAuto =
        Area(areasPodio.at(kv.first).x_ * CONFIG_CLIENTE.anchoVentana(),
             areasPodio.at(kv.first).y_ * CONFIG_CLIENTE.altoVentana(),
             animacion.ancho(),
             animacion.alto());
    renderizador_.dibujar(animacion.get(nroIteracion),
                          areaAuto,
                          0,
                          false);
  }
}

EscenaPodio::EscenaPodio(Renderizador &renderizador,
                         ColaProtegida<std::shared_ptr<EventoGUI>> &eventosGUI,
                         std::stack<std::shared_ptr<Escena>> &escenas,
                         ColaBloqueante<std::shared_ptr<Evento>> &eventosAEnviar_,
                         Sonido &musicaAmbiente,
                         std::map<int,
                                  std::shared_ptr<ObjetoDinamico>> &mapaAuto) :
    Escena(escenas, renderizador, eventosAEnviar_, musicaAmbiente
    ),
    fondoMenu_(AnimacionFactory::instanciar(CONFIG_CLIENTE.uuid("fondoPodio"),
                                            renderizador)
    ),
    eventosGUI_(eventosGUI), mapaAutos(mapaAuto) {
  this->musicaAmbiente.play();
  this->musicaAmbiente.setVolume(CONFIG_CLIENTE.volumenAmbiente());
  areasPodio.insert(std::pair<int, area_t>(0, {0.46, 0.52}));
  areasPodio.insert(std::pair<int, area_t>(1, {0.30, 0.56}));
  areasPodio.insert(std::pair<int, area_t>(2, {0.64, 0.60}));
}

Textura EscenaPodio::dibujate(uint32_t numeroIteracion, Area dimensiones) {
  Textura miTextura(renderizador_, dimensiones);
  renderizador_.setDestino(miTextura);
  Area areaFondo = Area(0, 0, dimensiones.ancho(), dimensiones.alto());
  renderizador_.dibujar(fondoMenu_.get(numeroIteracion), areaFondo);
  dibujarAutos(numeroIteracion);
  return miTextura;
}

void EscenaPodio::manejarInput(EventoGUI &evento) {
  evento.actualizar(*this);
}

void EscenaPodio::manejarInput(EventoGUIClick &evento) {
  /*int x, y;
  SDL_GetMouseState(&x, &y);
  for (const auto &boton: botones) {
    if (boton.second.get()->estaSeleccionado(x, y)) {
      handlerBotones(boton.first);
      break;
    }
  }*/
}

void EscenaPodio::manejarInput(EventoGUIKeyDown &evento) {
  if (evento.getTecla() == TECLA_ESC) {
    while (escenas_.size() > 1) {
      escenas_.pop();
    }
  }
  if (evento.getTecla() == TECLA_FULLSCREEN) {
    renderizador_.toggleFullScreen();
  }
}

void EscenaPodio::manejarInput(EventoGUIKeyUp &evento) {}

void EscenaPodio::manejar(Evento &e) {
  e.actualizar(*this);
}
