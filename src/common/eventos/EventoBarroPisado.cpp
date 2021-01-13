#include "includes/common/eventos/EventoBarroPisado.h"

#include "includes/common/Handler.h"

EventoBarroPisado::EventoBarroPisado(uint32_t uuidRemitente, Protocolo& protocolo) :
    Evento(uuidRemitente) {
}

EventoBarroPisado::EventoBarroPisado() :
    Evento(0) {
    
    UUIDEvento_ = UUID_EVENTO_BARRO_PISADO;
}

void EventoBarroPisado::enviarse(Protocolo& protocolo) {
    protocolo.enviar(UUIDEvento_);
}

void EventoBarroPisado::actualizar(Handler& handler) {
    handler.manejar(*this);
}
