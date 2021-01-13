#ifndef _EVENTO_FIN_BARRO_H_
#define _EVENTO_FIN_BARRO_H_

#include "includes/common/eventos/Evento.h"
#include "includes/common/red/Protocolo.h"

class EventoFinBarro : public Evento {
public:
    EventoFinBarro(uint32_t uuidRemitente, Protocolo& protocolo);
    EventoFinBarro();
    virtual void enviarse(Protocolo& protocolo) override;
    virtual void actualizar(Handler& handler) override;
};

#endif
