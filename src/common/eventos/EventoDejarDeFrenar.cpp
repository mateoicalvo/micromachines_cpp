#include "includes/common/eventos/EventoDejarDeFrenar.h"

#include "includes/common/Handler.h"

EventoDejarDeFrenar::EventoDejarDeFrenar(uint32_t uuidRemitente, Protocolo& protocolo) :
    Evento(uuidRemitente) {
}

EventoDejarDeFrenar::EventoDejarDeFrenar() :
    Evento(0) {        
    UUIDEvento_ = UUID_EVENTO_DEJAR_DE_FRENAR;
}

void EventoDejarDeFrenar::enviarse(Protocolo& protocolo) {
    protocolo.enviar(UUIDEvento_);
}

void EventoDejarDeFrenar::actualizar(Handler& handler) {
    handler.manejar(*this);
}
