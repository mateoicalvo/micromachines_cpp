#ifndef _EVENTO_CHOQUE_H_
#define _EVENTO_CHOQUE_H_

#include "includes/common/eventos/Evento.h"
#include "includes/common/red/Protocolo.h"

class EventoChoque : public Evento {
public:

    float xCoord_;
    float yCoord_;

    EventoChoque(uint32_t uuidRemitente, Protocolo& protocolo);
    EventoChoque(float xCoord, float yCoord);
    virtual void enviarse(Protocolo& protocolo) override;
    virtual void actualizar(Handler& handler) override;
};

#endif
