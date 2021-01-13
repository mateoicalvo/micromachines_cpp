#ifndef _EVENTO_FRENADA_H_
#define _EVENTO_FRENADA_H_

#include "includes/common/eventos/Evento.h"
#include "includes/common/red/Protocolo.h"

class EventoFrenada : public Evento {
public:

    float xCoord_;
    float yCoord_;

    EventoFrenada(uint32_t uuidRemitente, Protocolo& protocolo);
    EventoFrenada(float xCoord, float yCoord);
    virtual void enviarse(Protocolo& protocolo) override;
    virtual void actualizar(Handler& handler) override;
};

#endif
