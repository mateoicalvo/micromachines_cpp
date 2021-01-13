#ifndef _EVENTO_BARRO_PISADO_H_
#define _EVENTO_BARRO_PISADO_H_

#include "includes/common/eventos/Evento.h"
#include "includes/common/red/Protocolo.h"

class EventoBarroPisado : public Evento {
public:
    EventoBarroPisado(uint32_t uuidRemitente, Protocolo& protocolo);
    EventoBarroPisado();
    virtual void enviarse(Protocolo& protocolo) override;
    virtual void actualizar(Handler& handler) override;
};

#endif
