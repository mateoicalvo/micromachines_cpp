#include "includes/cliente/GUI/eventos/EventoGUIKeyUp.h"

#include "includes/cliente/GUI/EventoGUIHandler.h"

EventoGUIKeyUp::EventoGUIKeyUp(const std::string &tecla)
    : tecla_(std::move(tecla)) {
}

void EventoGUIKeyUp::actualizar(EventoGUIHandler &handler) {
  handler.manejarInput(*this);
}

std::string &EventoGUIKeyUp::getTecla() {
  return tecla_;
}

