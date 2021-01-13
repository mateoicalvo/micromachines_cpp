#ifndef _EVENTO_DEJAR_DE_DOBLAR_DERECHA_H_
#define _EVENTO_DEJAR_DE_DOBLAR_DERECHA_H_

#include "includes/common/eventos/Evento.h"
#include "includes/common/red/Protocolo.h"

class EventoDejarDeDoblarDerecha : public Evento {
public:
    EventoDejarDeDoblarDerecha(uint32_t uuidRemitente, Protocolo& protocolo);
    EventoDejarDeDoblarDerecha();
    virtual void enviarse(Protocolo& protocolo) override;
    virtual void actualizar(Handler& handler) override;
};

#endif
