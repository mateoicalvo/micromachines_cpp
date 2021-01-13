#ifndef _EVENTO_INICIAR_PARTIDA_H_
#define _EVENTO_INICIAR_PARTIDA_H_

#include "includes/common/eventos/Evento.h"
#include "includes/common/red/Protocolo.h"

class EventoIniciarPartida : public Evento {
public:
    EventoIniciarPartida(uint32_t uuidRemitente, Protocolo& protocolo);
    EventoIniciarPartida();
    virtual void enviarse(Protocolo& protocolo) override;
    virtual void actualizar(Handler& handler) override;
};

#endif
