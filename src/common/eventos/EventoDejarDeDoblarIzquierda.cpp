#include "includes/common/eventos/EventoDejarDeDoblarIzquierda.h"

#include "includes/common/Handler.h"

EventoDejarDeDoblarIzquierda::EventoDejarDeDoblarIzquierda(uint32_t uuidRemitente, Protocolo& protocolo) :
    Evento(uuidRemitente) {
}

EventoDejarDeDoblarIzquierda::EventoDejarDeDoblarIzquierda() :
    Evento(0) {        
    UUIDEvento_ = UUID_EVENTO_DEJAR_DE_DOBLAR_IZQUIERDA;
}

void EventoDejarDeDoblarIzquierda::enviarse(Protocolo& protocolo) {
    protocolo.enviar(UUIDEvento_);
}

void EventoDejarDeDoblarIzquierda::actualizar(Handler& handler) {
    handler.manejar(*this);
}
