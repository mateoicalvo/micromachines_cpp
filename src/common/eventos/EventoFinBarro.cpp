#include "includes/common/eventos/EventoFinBarro.h"

#include "includes/common/Handler.h"

EventoFinBarro::EventoFinBarro(uint32_t uuidRemitente, Protocolo& protocolo) :
    Evento(uuidRemitente) {
}

EventoFinBarro::EventoFinBarro() :
    Evento(0) {
    
    UUIDEvento_ = UUID_EVENTO_FIN_BARRO;
}

void EventoFinBarro::enviarse(Protocolo& protocolo) {
    protocolo.enviar(UUIDEvento_);
}

void EventoFinBarro::actualizar(Handler& handler) {
    handler.manejar(*this);
}
