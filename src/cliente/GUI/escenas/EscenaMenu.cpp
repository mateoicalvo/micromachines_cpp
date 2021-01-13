#include <iostream>
#include "includes/cliente/GUI/escenas/EscenaMenu.h"
#include "includes/cliente/GUI/escenas/EscenaPartida.h"
#include "includes/cliente/GUI/escenas/EscenaSala.h"
#include "includes/cliente/GUI/AnimacionFactory.h"
#include "includes/cliente/utils/ConfigCliente.h"
#include "includes/cliente/GUI/Area.h"

void EscenaMenu::inicializarBotones() {
  this->botones.insert(std::pair<int, std::shared_ptr<Boton>>(
      UUID_BOTON_JUGAR,
      std::make_shared<Boton>(UUID_BOTON_JUGAR,
                              renderizador_,
                              0.41
                                  * CONFIG_CLIENTE.anchoVentana(),
                              0.60
                                  * CONFIG_CLIENTE.altoVentana())));
  this->botones.insert(std::pair<int, std::shared_ptr<Boton>>(
      UUID_BOTON_SALIR,
      std::make_shared<Boton>(UUID_BOTON_SALIR,
                              renderizador_,
                              0.41
                                  * CONFIG_CLIENTE.anchoVentana(),
                              0.70
                                  * CONFIG_CLIENTE.altoVentana())));
}

void EscenaMenu::dibujarBotones(int nroIteracion) {
  for (const auto &boton: botones) {
    Animacion &animacion = boton.second.get()->getAnimacion();
    Area areaBoton = Area(boton.second.get()->getX(),
                          boton.second.get()->getY(),
                          animacion.ancho(),
                          animacion.alto());
    renderizador_.dibujar(animacion.get(nroIteracion), areaBoton);
  }
}

void EscenaMenu::handlerBotones(int uuid) {
  switch (uuid) {
    case UUID_BOTON_JUGAR: {
      std::shared_ptr<Evento> unirme = std::make_shared<EventoUnirseASala>();
      eventosAEnviar_.put(unirme);
      quiereEntrarASala = true;
      break;
    }
    case UUID_BOTON_SALIR: {
      seguirCorriendoCliente = false;
      break;
    }
    default:break;
  }
}

EscenaMenu::EscenaMenu(Renderizador &renderizador,
                       ColaProtegida<std::shared_ptr<EventoGUI>> &eventosGUI,
                       std::stack<std::shared_ptr<Escena>> &escenas,
                       ColaBloqueante<std::shared_ptr<Evento>> &eventosAEnviar_,
                       Sonido &musicaAmbiente, bool &seguirCorriendo) :
    Escena(escenas, renderizador, eventosAEnviar_, musicaAmbiente),
    fondoMenu_(AnimacionFactory::instanciar(CONFIG_CLIENTE.uuid("fondoMenu"),
                                            renderizador)),
    eventosGUI_(eventosGUI),
    quiereEntrarASala(false),
    seguirCorriendoCliente(seguirCorriendo) {
  inicializarBotones();
  this->musicaAmbiente.setVolume(CONFIG_CLIENTE.volumenAmbiente());
  this->musicaAmbiente.play();
}

Textura EscenaMenu::dibujate(uint32_t numeroIteracion, Area dimensiones) {
  Textura miTextura(renderizador_, dimensiones);
  renderizador_.setDestino(miTextura);
  Area areaFondo = Area(0, 0, dimensiones.ancho(), dimensiones.alto());
  renderizador_.dibujar(fondoMenu_.get(numeroIteracion), areaFondo);
  dibujarBotones(numeroIteracion);
  return miTextura;
}

void EscenaMenu::manejarInput(EventoGUI &evento) {
  evento.actualizar(*this);
}

void EscenaMenu::manejarInput(EventoGUIClick &evento) {
  int x, y;
  SDL_GetMouseState(&x, &y);
  for (const auto &boton: botones) {
    if (boton.second.get()->estaSeleccionado(x, y)) {
      handlerBotones(boton.first);
      break;
    }
  }
}

void EscenaMenu::manejarInput(EventoGUIKeyDown &evento) {
  if (evento.getTecla() == TECLA_FULLSCREEN) {
    renderizador_.toggleFullScreen();
  }
}

void EscenaMenu::manejarInput(EventoGUIKeyUp &evento) {}

void EscenaMenu::manejar(Evento &e) {
  e.actualizar(*this);
}

void EscenaMenu::manejar(EventoSnapshotSala &e) {
  if (!quiereEntrarASala) {
    return;
  }
  escenas_.emplace(std::make_shared<EscenaSala>(renderizador_,
                                                eventosGUI_,
                                                escenas_,
                                                eventosAEnviar_,
                                                this->musicaAmbiente,
                                                e));
}
