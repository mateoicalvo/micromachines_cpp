#include "includes/common/eventos/EventoPartidaCreada.h"

#include "includes/common/Handler.h"

EventoPartidaCreada::EventoPartidaCreada(uint32_t uuidRemitente, Protocolo& protocolo) :
    Evento(uuidRemitente) {
    uuidPartida_ = protocolo.recibirNumUnsigned16();
    uuidCreador_ = protocolo.recibirNumUnsigned32();
}

EventoPartidaCreada::EventoPartidaCreada(uint16_t uuidPartida, uint32_t uuidCreador) :
    Evento(0),
    uuidPartida_(uuidPartida),
    uuidCreador_(uuidCreador) {
    
    UUIDEvento_ = UUID_EVENTO_PARTIDA_CREADA;
}

void EventoPartidaCreada::enviarse(Protocolo& protocolo) {
    protocolo.enviar(UUIDEvento_);
    protocolo.enviar(uuidPartida_);
    protocolo.enviar(uuidCreador_);
}

void EventoPartidaCreada::actualizar(Handler& handler) {
    handler.manejar(*this);
}
