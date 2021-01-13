#include "includes/common/eventos/EventoFrenar.h"

#include "includes/common/Handler.h"

EventoFrenar::EventoFrenar(uint32_t uuidRemitente, Protocolo& protocolo) :
    Evento(uuidRemitente) {
}

EventoFrenar::EventoFrenar() :
    Evento(0) {        
    UUIDEvento_ = UUID_EVENTO_FRENAR;
}

void EventoFrenar::enviarse(Protocolo& protocolo) {
    protocolo.enviar(UUIDEvento_);
}

void EventoFrenar::actualizar(Handler& handler) {
    handler.manejar(*this);
}
