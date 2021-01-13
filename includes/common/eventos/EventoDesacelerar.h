#ifndef _EVENTO_DESACELERAR_H_
#define _EVENTO_DESACELERAR_H_

#include "includes/common/eventos/Evento.h"
#include "includes/common/red/Protocolo.h"

class EventoDesacelerar : public Evento {
public:
    EventoDesacelerar(uint32_t uuidRemitente, Protocolo& protocolo);
    EventoDesacelerar();
    virtual void enviarse(Protocolo& protocolo) override;
    virtual void actualizar(Handler& handler) override;
};

#endif
