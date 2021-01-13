#ifndef _EVENTO_PARTIDA_INICIADA_H_
#define _EVENTO_PARTIDA_INICIADA_H_

#include "includes/common/eventos/Evento.h"
#include "includes/common/eventos/EventoSnapshot.h"
#include "includes/common/red/Protocolo.h"

class EventoPartidaIniciada : public Evento {

public:
    uint8_t idDelVehiculo_;
    EventoSnapshot estadoInicial_;

    EventoPartidaIniciada(uint32_t uuidRemitente, Protocolo& protocolo);
    EventoPartidaIniciada(uint8_t idDelVehiculo, std::map<uint8_t, datosVehiculo_>&& datos);
    virtual void enviarse(Protocolo& protocolo) override;
    virtual void actualizar(Handler& handler) override;
};

#endif
