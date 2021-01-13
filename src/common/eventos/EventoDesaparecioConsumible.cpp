#include "includes/common/eventos/EventoDesaparecioConsumible.h"

#include "includes/common/Handler.h"

EventoDesaparecioConsumible::EventoDesaparecioConsumible(uint32_t uuidRemitente, Protocolo& protocolo) :
    Evento(uuidRemitente) {
    uuidConsumible_ = protocolo.recibirNumUnsigned8();
}

EventoDesaparecioConsumible::EventoDesaparecioConsumible(uint8_t uuidConsumible) :
    Evento(0),
    uuidConsumible_(uuidConsumible) {
    
    UUIDEvento_ = UUID_EVENTO_DESAPARECIO_CONSUMIBLE;
}

void EventoDesaparecioConsumible::enviarse(Protocolo& protocolo) {
    protocolo.enviar(UUIDEvento_);
    protocolo.enviar(uuidConsumible_);
}

void EventoDesaparecioConsumible::actualizar(Handler& handler) {
    handler.manejar(*this);
}
