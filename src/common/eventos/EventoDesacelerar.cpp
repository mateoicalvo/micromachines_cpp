#include "includes/common/eventos/EventoDesacelerar.h"

#include "includes/common/Handler.h"

EventoDesacelerar::EventoDesacelerar(uint32_t uuidRemitente, Protocolo& protocolo) :
    Evento(uuidRemitente) {
}

EventoDesacelerar::EventoDesacelerar() :
    Evento(0) {        
    UUIDEvento_ = UUID_EVENTO_DESACELERAR;
}

void EventoDesacelerar::enviarse(Protocolo& protocolo) {
    protocolo.enviar(UUIDEvento_);
}

void EventoDesacelerar::actualizar(Handler& handler) {
    handler.manejar(*this);
}
