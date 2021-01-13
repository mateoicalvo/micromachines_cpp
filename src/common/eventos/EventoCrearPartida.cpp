#include "includes/common/eventos/EventoCrearPartida.h"

#include "includes/common/Handler.h"

EventoCrearPartida::EventoCrearPartida(uint32_t uuidRemitente, Protocolo &protocolo) :
    Evento(uuidRemitente) {
}

EventoCrearPartida::EventoCrearPartida() : Evento(0) {
  this->UUIDEvento_ = UUID_EVENTO_CREAR_PARTIDA;
}

void EventoCrearPartida::enviarse(Protocolo &protocolo) {
  protocolo.enviar(UUIDEvento_);
}

void EventoCrearPartida::actualizar(Handler &handler) {
  handler.manejar(*this);
}
