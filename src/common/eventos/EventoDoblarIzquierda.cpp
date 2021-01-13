#include "includes/common/eventos/EventoDoblarIzquierda.h"

#include "includes/common/Handler.h"

EventoDoblarIzquierda::EventoDoblarIzquierda(uint32_t uuidRemitente, Protocolo& protocolo) :
    Evento(uuidRemitente) {
}

EventoDoblarIzquierda::EventoDoblarIzquierda() :
    Evento(0) {        
    UUIDEvento_ = UUID_EVENTO_DOBLAR_IZQUIERDA;
}

void EventoDoblarIzquierda::enviarse(Protocolo& protocolo) {
    protocolo.enviar(UUIDEvento_);
}

void EventoDoblarIzquierda::actualizar(Handler& handler) {
    handler.manejar(*this);
}
