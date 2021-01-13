#include "includes/common/eventos/EventoIniciarPartida.h"

#include "includes/common/Handler.h"

EventoIniciarPartida::EventoIniciarPartida(uint32_t uuidRemitente, Protocolo &protocolo) :
    Evento(uuidRemitente) {
}

EventoIniciarPartida::EventoIniciarPartida() : Evento(0) {
  this->UUIDEvento_ = UUID_EVENTO_INICIAR_PARTIDA;
}

void EventoIniciarPartida::enviarse(Protocolo &protocolo) {
  protocolo.enviar(UUIDEvento_);
}

void EventoIniciarPartida::actualizar(Handler &handler) {
  handler.manejar(*this);
}
