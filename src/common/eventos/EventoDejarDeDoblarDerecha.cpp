#include "includes/common/eventos/EventoDejarDeDoblarDerecha.h"

#include "includes/common/Handler.h"

EventoDejarDeDoblarDerecha::EventoDejarDeDoblarDerecha(uint32_t uuidRemitente, Protocolo& protocolo) :
    Evento(uuidRemitente) {
}

EventoDejarDeDoblarDerecha::EventoDejarDeDoblarDerecha() :
    Evento(0) {        
    UUIDEvento_ = UUID_EVENTO_DEJAR_DE_DOBLAR_DERECHA;
}

void EventoDejarDeDoblarDerecha::enviarse(Protocolo& protocolo) {
    protocolo.enviar(UUIDEvento_);
}

void EventoDejarDeDoblarDerecha::actualizar(Handler& handler) {
    handler.manejar(*this);
}
