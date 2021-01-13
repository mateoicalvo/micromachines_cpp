#ifndef _EVENTO_SNAPSHOT_LOBBY_H_
#define _EVENTO_SNAPSHOT_LOBBY_H_

#include <map>

#include "includes/common/eventos/Evento.h"
#include "includes/common/red/Protocolo.h"

class EventoSnapshotLobby : public Evento {
public:
    uint8_t cantidadJugadores_;
    std::map<uint32_t, bool> idJugadorAEstaListo_;

    EventoSnapshotLobby(uint32_t uuidRemitente, Protocolo& protocolo);
    EventoSnapshotLobby(std::map<uint32_t, bool>&& datos);
    virtual void enviarse(Protocolo& protocolo) override;
    virtual void actualizar(Handler& handler) override;
};

#endif
