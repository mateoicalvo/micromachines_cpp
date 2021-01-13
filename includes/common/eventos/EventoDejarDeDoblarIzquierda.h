#ifndef _EVENTO_DEJAR_DE_DOBLAR_IZQUIERDA_H_
#define _EVENTO_DEJAR_DE_DOBLAR_IZQUIERDA_H_

#include "includes/common/eventos/Evento.h"
#include "includes/common/red/Protocolo.h"

class EventoDejarDeDoblarIzquierda : public Evento {
public:
    EventoDejarDeDoblarIzquierda(uint32_t uuidRemitente, Protocolo& protocolo);
    EventoDejarDeDoblarIzquierda();
    virtual void enviarse(Protocolo& protocolo) override;
    virtual void actualizar(Handler& handler) override;
};

#endif
