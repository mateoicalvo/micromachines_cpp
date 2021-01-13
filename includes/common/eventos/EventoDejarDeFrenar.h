#ifndef _EVENTO_DEJAR_DE_FRENAR_H_
#define _EVENTO_DEJAR_DE_FRENAR_H_

#include "includes/common/eventos/Evento.h"
#include "includes/common/red/Protocolo.h"

class EventoDejarDeFrenar : public Evento {
public:
    EventoDejarDeFrenar(uint32_t uuidRemitente, Protocolo& protocolo);
    EventoDejarDeFrenar();
    virtual void enviarse(Protocolo& protocolo) override;
    virtual void actualizar(Handler& handler) override;
};

#endif
