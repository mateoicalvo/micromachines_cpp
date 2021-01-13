#include "includes/servidor/Jugador.h"

Jugador::Jugador(SocketTCP&& socket, uint32_t uuid, ColaBloqueante<std::shared_ptr<Evento>>& destinoEventos) :
    UUID_(uuid),
    socket_(std::move(socket)),
    destino_(destinoEventos),
    recibidorEventos_(socket_, destino_, UUID_),
    enviadorEventos_(socket_, eventosAEnviar_) {
    
    recibidorEventos_.iniciar();
    enviadorEventos_.iniciar();
}

Jugador::~Jugador() {
    eventosAEnviar_.detener();
    
    socket_.cerrarLectoEscritura();
    
    recibidorEventos_.detener();
    recibidorEventos_.join();
    
    enviadorEventos_.detener();
    enviadorEventos_.join();
}

uint32_t Jugador::uuid () {
    return UUID_;
}

void Jugador::ocurrio(std::shared_ptr<Evento> e) {
    eventosAEnviar_.put(e);
}
