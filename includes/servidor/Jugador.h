#ifndef _JUGADOR_H_
#define _JUGADOR_H_

#include <memory>

#include "includes/common/Handler.h"
#include "includes/common/red/SocketTCP.h"
#include "includes/common/ColaBloqueante.h"
#include "includes/common/eventos/Evento.h"
#include "includes/common/RecibidorEventos.h"
#include "includes/common/EnviadorEventos.h"

class Jugador {
private:
    uint32_t UUID_;
    SocketTCP socket_;
    ColaBloqueante<std::shared_ptr<Evento>>& destino_;
    ColaBloqueante<std::shared_ptr<Evento>> eventosAEnviar_;
    RecibidorEventos recibidorEventos_;
    EnviadorEventos enviadorEventos_;
    

public:
    Jugador(SocketTCP&& socket, uint32_t uuid, ColaBloqueante<std::shared_ptr<Evento>>& destinoEventos);
    ~Jugador();
    uint32_t uuid();
    //TODO: QUE ESTO SEA UNA ITNTERFAZ
    void ocurrio(std::shared_ptr<Evento> e);
};

#endif
