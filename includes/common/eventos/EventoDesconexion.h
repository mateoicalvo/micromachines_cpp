#ifndef _EVENTO_DESCONEXION_H_
#define _EVENTO_DESCONEXION_H_

#include "includes/common/eventos/Evento.h"
#include "includes/common/red/Protocolo.h"

class EventoDesconexion : public Evento {
public:
    EventoDesconexion(uint32_t uuidRemitente);
    EventoDesconexion(uint32_t uuidRemitente, Protocolo& protocolo);
    virtual void enviarse(Protocolo& protocolo);
    virtual void actualizar(Handler& handler) override;
};

#endif
