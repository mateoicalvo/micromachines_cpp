#include "includes/common/eventos/EventoFrenada.h"

#include "includes/common/Handler.h"

EventoFrenada::EventoFrenada(uint32_t uuidRemitente, Protocolo& protocolo) :
    Evento(uuidRemitente) {
        
    uint16_t xCoordRed = protocolo.recibirNumUnsigned32();
    xCoord_ = (float)xCoordRed / 100.0f;
    uint16_t yCoordRed = protocolo.recibirNumUnsigned32();
    yCoord_ = (float)yCoordRed / 100.0f;
}

EventoFrenada::EventoFrenada(float xCoord, float yCoord) :
    Evento(0),
    xCoord_(xCoord),
    yCoord_(yCoord) {
    
    UUIDEvento_ = UUID_EVENTO_FRENADA;
}

void EventoFrenada::enviarse(Protocolo& protocolo) {
    protocolo.enviar(UUIDEvento_);
    uint32_t xCoordRed = 100 * xCoord_;
    protocolo.enviar(xCoordRed);
    uint32_t yCoordRed = 100 * yCoord_;
    protocolo.enviar(yCoordRed);
}

void EventoFrenada::actualizar(Handler& handler) {
    handler.manejar(*this);
}
