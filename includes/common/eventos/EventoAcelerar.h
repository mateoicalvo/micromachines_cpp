#ifndef _EVENTO_ACELERAR_H_
#define _EVENTO_ACELERAR_H_

#include "includes/common/eventos/Evento.h"
#include "includes/common/red/Protocolo.h"

class EventoAcelerar : public Evento {
public:
    EventoAcelerar(uint32_t uuidRemitente, Protocolo& protocolo);
    EventoAcelerar();
    virtual void enviarse(Protocolo& protocolo) override;
    virtual void actualizar(Handler& handler) override;
};

#endif
