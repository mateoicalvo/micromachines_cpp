#include "includes/common/eventos/EventoDoblarDerecha.h"

#include "includes/common/Handler.h"

EventoDoblarDerecha::EventoDoblarDerecha(uint32_t uuidRemitente, Protocolo& protocolo) :
    Evento(uuidRemitente) {
}

EventoDoblarDerecha::EventoDoblarDerecha() :
    Evento(0) {        
    UUIDEvento_ = UUID_EVENTO_DOBLAR_DERECHA;
}

void EventoDoblarDerecha::enviarse(Protocolo& protocolo) {
    protocolo.enviar(UUIDEvento_);
}

void EventoDoblarDerecha::actualizar(Handler& handler) {
    handler.manejar(*this);
}
