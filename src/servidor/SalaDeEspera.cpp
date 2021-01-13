#include "includes/servidor/SalaDeEspera.h"

SalaDeEspera::SalaDeEspera(ColaBloqueante<std::shared_ptr<Evento>>& destinoEventos) :
    contadorJugadores_(0),
    destinoEventos_(destinoEventos) {
}

SalaDeEspera::~SalaDeEspera() {
    
}

void SalaDeEspera::agregarJugador(SocketTCP&& socket) {
    std::lock_guard<std::mutex> lck(mtx_);
    contadorJugadores_++;
    jugadores_[contadorJugadores_] = std::make_shared<Jugador>(std::move(socket), contadorJugadores_, destinoEventos_);
}

void SalaDeEspera::agregarJugador(std::shared_ptr<Jugador> unJugador) {
    std::lock_guard<std::mutex> lck(mtx_);
    jugadores_[unJugador->uuid()] = unJugador;
}

std::shared_ptr<Jugador> SalaDeEspera::quitarJugador(uint32_t uuidJugador) {
    std::lock_guard<std::mutex> lck(mtx_);
    std::shared_ptr<Jugador> jugador = jugadores_.at(uuidJugador);
    jugadores_.erase(uuidJugador);
    return jugador;
}

std::shared_ptr<Jugador> SalaDeEspera::getJugador(uint32_t uuidJugador) { 
    std::lock_guard<std::mutex> lck(mtx_);
    return jugadores_.at(uuidJugador);
}

void SalaDeEspera::ocurrio(std::shared_ptr<Evento> unEvento) {
    for (const auto& kv : jugadores_) {
        kv.second->ocurrio(unEvento);
    }
}

void SalaDeEspera::manejar(Evento& e) {
    e.actualizar(*this);
}

void SalaDeEspera::manejar(EventoDesconexion& e) {
    //FIXME: Mejorar esta lógica
    std::lock_guard<std::mutex> lck(mtx_);
    jugadores_.erase(e.uuidRemitente());
}
