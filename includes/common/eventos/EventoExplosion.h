#ifndef _EVENTO_EXPLOSION_H_
#define _EVENTO_EXPLOSION_H_

#include "includes/common/eventos/Evento.h"
#include "includes/common/red/Protocolo.h"

class EventoExplosion : public Evento {
public:

    float xCoord_;
    float yCoord_;

    EventoExplosion(uint32_t uuidRemitente, Protocolo& protocolo);
    EventoExplosion(float xCoord, float yCoord);
    virtual void enviarse(Protocolo& protocolo) override;
    virtual void actualizar(Handler& handler) override;
};

#endif
