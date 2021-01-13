#include "includes/common/eventos/EventoUnirseAPartida.h"

#include "includes/common/Handler.h"

EventoUnirseAPartida::EventoUnirseAPartida(uint32_t uuidRemitente, Protocolo &protocolo) :
    Evento(uuidRemitente) {
  uuidPartida_ = protocolo.recibirNumUnsigned16();
}

EventoUnirseAPartida::EventoUnirseAPartida(uint32_t uuidRemitente, uint16_t uuidPartida) :
    Evento(uuidRemitente),
    uuidPartida_(uuidPartida) {
}

EventoUnirseAPartida::EventoUnirseAPartida(uint16_t uuidPartida) : Evento(0) {
  this->UUIDEvento_ = UUID_EVENTO_UNIRSE_A_PARTIDA;
  this->uuidPartida_ = uuidPartida;
}
void EventoUnirseAPartida::enviarse(Protocolo &protocolo) {
  protocolo.enviar(UUIDEvento_);
  protocolo.enviar(uuidPartida_);
}

void EventoUnirseAPartida::actualizar(Handler &handler) {
  handler.manejar(*this);
}
