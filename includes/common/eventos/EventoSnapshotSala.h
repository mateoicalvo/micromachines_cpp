#ifndef _EVENTO_SNAPSHOT_SALA_H_
#define _EVENTO_SNAPSHOT_SALA_H_

#include <map>

#include "includes/common/eventos/Evento.h"
#include "includes/common/red/Protocolo.h"

class EventoSnapshotSala : public Evento {
public:
    uint16_t cantidadPartidas_;
    std::map<uint16_t, uint16_t> ordinalAuuidPartida_;

    EventoSnapshotSala(uint32_t uuidRemitente, Protocolo& protocolo);
    EventoSnapshotSala(std::map<uint16_t, uint16_t>&& datos);
    virtual void enviarse(Protocolo& protocolo) override;
    virtual void actualizar(Handler& handler) override;
};

#endif
