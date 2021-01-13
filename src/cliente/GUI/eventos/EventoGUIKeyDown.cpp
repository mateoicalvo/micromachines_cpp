#include "includes/cliente/GUI/eventos/EventoGUIKeyDown.h"

#include "includes/cliente/GUI/EventoGUIHandler.h"

EventoGUIKeyDown::EventoGUIKeyDown(const std::string& tecla)
    : tecla_(std::move(tecla)) {
}

void EventoGUIKeyDown::actualizar(EventoGUIHandler& handler) {
  handler.manejarInput(*this);
}

std::string& EventoGUIKeyDown::getTecla() {
    return tecla_;
}
