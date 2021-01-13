#ifndef _EVENTO_DESAPARECIO_CONSUMIBLE_H_
#define _EVENTO_DESAPARECIO_CONSUMIBLE_H_

#include "includes/common/eventos/Evento.h"
#include "includes/common/red/Protocolo.h"

class EventoDesaparecioConsumible : public Evento {
public:
    uint8_t uuidConsumible_;

    EventoDesaparecioConsumible(uint32_t uuidRemitente, Protocolo& protocolo);
    EventoDesaparecioConsumible(uint8_t uuidConsumible);
    virtual void enviarse(Protocolo& protocolo) override;
    virtual void actualizar(Handler& handler) override;
};

#endif
