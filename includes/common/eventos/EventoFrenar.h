#ifndef _EVENTO_FRENAR_H_
#define _EVENTO_FRENAR_H_

#include "includes/common/eventos/Evento.h"
#include "includes/common/red/Protocolo.h"

class EventoFrenar : public Evento {
public:
    EventoFrenar(uint32_t uuidRemitente, Protocolo& protocolo);
    EventoFrenar();
    virtual void enviarse(Protocolo& protocolo) override;
    virtual void actualizar(Handler& handler) override;
};

#endif
