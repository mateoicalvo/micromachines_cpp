#include "includes/common/eventos/EventoDesconexion.h"

#include "includes/common/Handler.h"

EventoDesconexion::EventoDesconexion(uint32_t uuidRemitente) :
    Evento(uuidRemitente) {
    
}

EventoDesconexion::EventoDesconexion(uint32_t uuidRemitente, Protocolo& protocolo) :
    Evento(uuidRemitente) {
}

void EventoDesconexion::enviarse(Protocolo& protocolo) {

}

void EventoDesconexion::actualizar(Handler& handler) {
    handler.manejar(*this);
}
