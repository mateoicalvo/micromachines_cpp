#include "includes/cliente/GUI/eventos/EventoGUIClick.h"

#include "includes/cliente/GUI/EventoGUIHandler.h"

EventoGUIClick::EventoGUIClick(unsigned int x, unsigned int y)
    : x_(x)
    , y_(y) {
}

void EventoGUIClick::actualizar(EventoGUIHandler& handler) {
  handler.manejarInput(*this);
}
