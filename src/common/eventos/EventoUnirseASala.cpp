#include "includes/common/eventos/EventoUnirseASala.h"

#include "includes/common/Handler.h"

EventoUnirseASala::EventoUnirseASala(uint32_t uuidRemitente, Protocolo& protocolo) :
    Evento(uuidRemitente) {
}

EventoUnirseASala::EventoUnirseASala() :
    Evento(0) {
    
    UUIDEvento_ = UUID_EVENTO_UNIRSE_A_SALA;
}

void EventoUnirseASala::enviarse(Protocolo& protocolo) {
    protocolo.enviar(UUIDEvento_);
}

void EventoUnirseASala::actualizar(Handler& handler) {
    handler.manejar(*this);
}
