#ifndef _EVENTO_DOBLAR_DERECHA_H_
#define _EVENTO_DOBLAR_DERECHA_H_

#include "includes/common/eventos/Evento.h"
#include "includes/common/red/Protocolo.h"

class EventoDoblarDerecha : public Evento {
public:
    EventoDoblarDerecha(uint32_t uuidRemitente, Protocolo& protocolo);
    EventoDoblarDerecha();
    virtual void enviarse(Protocolo& protocolo) override;
    virtual void actualizar(Handler& handler) override;
};

#endif
