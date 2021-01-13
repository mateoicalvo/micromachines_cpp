#include "includes/common/eventos/EventoExplosion.h"

#include "includes/common/Handler.h"

EventoExplosion::EventoExplosion(uint32_t uuidRemitente, Protocolo& protocolo) :
    Evento(uuidRemitente) {

    uint16_t xCoordRed = protocolo.recibirNumUnsigned32();
    xCoord_ = (float)xCoordRed / 100.0f;
    uint16_t yCoordRed = protocolo.recibirNumUnsigned32();
    yCoord_ = (float)yCoordRed / 100.0f;
}

EventoExplosion::EventoExplosion(float xCoord, float yCoord) :
    Evento(0),
    xCoord_(xCoord),
    yCoord_(yCoord) {
    
    UUIDEvento_ = UUID_EVENTO_EXPLOSION;
}

void EventoExplosion::enviarse(Protocolo& protocolo) {
    protocolo.enviar(UUIDEvento_);
    uint32_t xCoordRed = 100 * xCoord_;
    protocolo.enviar(xCoordRed);
    uint32_t yCoordRed = 100 * yCoord_;
    protocolo.enviar(yCoordRed);
}

void EventoExplosion::actualizar(Handler& handler) {
    handler.manejar(*this);
}
