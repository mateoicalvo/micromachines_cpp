#ifndef _EVENTO_DOBLAR_IZQUIERDA_H_
#define _EVENTO_DOBLAR_IZQUIERDA_H_

#include "includes/common/eventos/Evento.h"
#include "includes/common/red/Protocolo.h"

class EventoDoblarIzquierda : public Evento {
public:
    EventoDoblarIzquierda(uint32_t uuidRemitente, Protocolo& protocolo);
    EventoDoblarIzquierda();
    virtual void enviarse(Protocolo& protocolo) override;
    virtual void actualizar(Handler& handler) override;
};

#endif
