#include "includes/common/eventos/EventoAcelerar.h"

#include "includes/common/Handler.h"

EventoAcelerar::EventoAcelerar(uint32_t uuidRemitente, Protocolo& protocolo) :
    Evento(uuidRemitente) {
}

EventoAcelerar::EventoAcelerar() :
    Evento(0) {        
    UUIDEvento_ = UUID_EVENTO_ACELERAR;
}

void EventoAcelerar::enviarse(Protocolo& protocolo) {
    protocolo.enviar(UUIDEvento_);
}

void EventoAcelerar::actualizar(Handler& handler) {
    handler.manejar(*this);
}
