#ifndef _EVENTO_UNIRSE_A_SALA_H_
#define _EVENTO_UNIRSE_A_SALA_H_

#include "includes/common/eventos/Evento.h"
#include "includes/common/red/Protocolo.h"

class EventoUnirseASala : public Evento {
public:
    EventoUnirseASala(uint32_t uuidRemitente, Protocolo& protocolo);
    EventoUnirseASala();
    virtual void enviarse(Protocolo& protocolo) override;
    virtual void actualizar(Handler& handler) override;
};

#endif
