#include "includes/servidor/CoordinadorPartidas.h"

CoordinadorPartidas::CoordinadorPartidas(SalaDeEspera& salaDeEspera) :
    contadorPartidas_(0),
    salaDeEspera_(salaDeEspera){
}

CoordinadorPartidas::~CoordinadorPartidas() {
    for (const auto& kv : partidas_) {
        if (kv.second->estaCorriendo()) {
            kv.second->detener();
        }
        kv.second->join();
    }
}

void CoordinadorPartidas::agregarJugadorAPartida(std::shared_ptr<Jugador> jugador, uint16_t uuidPartida) {
    partidas_.at(uuidPartida)->agregarJugador(jugador);
    jugadoresAPartidas_[jugador->uuid()] = uuidPartida;
    for (const auto& kv : partidas_.at(uuidPartida)->jugadores()) {
        kv.second->ocurrio(getSnapshotLobby(uuidPartida));
    }
}

std::shared_ptr<EventoSnapshotSala> CoordinadorPartidas::getSnapshotSala() {
    std::map<uint16_t, uint16_t> datosSnapshot;
    uint16_t ordinal = 1;
    for (const auto& kv : partidas_) {
        //FIXME: PREGUNTAR POR ESTACORRIENDO LA ELIMINACION "ORDENADA" TIENE QUE HACERSE EN UN SOLO LUGAR
        if (!kv.second->aceptaJugadores()) {
            continue;
        }
        datosSnapshot.emplace(ordinal, kv.first);
        ordinal++;
    }    
    return std::make_shared<EventoSnapshotSala>(std::move(datosSnapshot));
}

std::shared_ptr<EventoSnapshotLobby> CoordinadorPartidas::getSnapshotLobby(uint16_t uuidPartida) {
    std::map<uint32_t, bool> datosDelvento;
    std::shared_ptr<Partida> partida = partidas_.at(uuidPartida);
    std::map<uint32_t, std::shared_ptr<Jugador>> jugadoresEnPartida = partida->jugadores();
    for (const auto& kv : jugadoresEnPartida) {
        //FIXME: Agregar logica de estoy listo
        datosDelvento.emplace(kv.first, partida->estaListo(kv.first));
    }
    return std::make_shared<EventoSnapshotLobby>(std::move(datosDelvento));        
}

void CoordinadorPartidas::manejar(Evento& e) {
    e.actualizar(*this);
}

void CoordinadorPartidas::manejar(EventoCrearPartida& e) {
    //FIXME: Si contadorPartidas da la vuelta a 0, lanzar error o soucionarlo
    contadorPartidas_++;
    // TODO: Acá hay que decir que uuid de mapa se quiere cargar
    // FIXME: No hardcodear esto
    uint16_t uuidPista = 1;
    partidas_[contadorPartidas_] = std::make_shared<Partida>(uuidPista, salaDeEspera_);
    std::shared_ptr<Evento> partidaCreada = std::make_shared<EventoPartidaCreada>(contadorPartidas_, e.uuidRemitente());
    salaDeEspera_.getJugador(e.uuidRemitente())->ocurrio(partidaCreada);
    salaDeEspera_.ocurrio(getSnapshotSala());
    //FIXME: Quitar partidas finalizadas, que no deben tener jugadores dentro (En realidad no iporta)

}

//FIXME: Debería esperar que todos envíen jugar.
void CoordinadorPartidas::manejar(EventoIniciarPartida& e) {
    uint32_t uuidJugador = e.uuidRemitente();
    uint16_t uuidPartida = jugadoresAPartidas_[uuidJugador];
    std::shared_ptr<Partida> partida = partidas_.at(uuidPartida);
    partida->marcarListo(uuidJugador);
    for (const auto& kv : partidas_.at(uuidPartida)->jugadores()) {
        kv.second->ocurrio(getSnapshotLobby(uuidPartida));
    }
    if (partida->todosListos()) {
        partidas_[uuidPartida]->iniciar();
    }
}

void CoordinadorPartidas::manejar(EventoDesconexion& e) {
    //TODO: enviar a la partida correspondiente el
    //evento desconexion para que se quite al jugador.
    //partidas_[1]->manejar(e);
    //partidas_.erase(1);
}

void CoordinadorPartidas::manejar(EventoAcelerar& e) {
    uint32_t uuidJugador = e.uuidRemitente();
    uint16_t uuidPartida = jugadoresAPartidas_[uuidJugador];
    std::shared_ptr<Evento> evento = std::make_shared<EventoAcelerar>(std::move(e));
    partidas_[uuidPartida]->ocurrio(evento);
}


void CoordinadorPartidas::manejar(EventoDesacelerar& e) {
    uint32_t uuidJugador = e.uuidRemitente();
    uint16_t uuidPartida = jugadoresAPartidas_[uuidJugador];
    std::shared_ptr<Evento> evento = std::make_shared<EventoDesacelerar>(std::move(e));
    partidas_[uuidPartida]->ocurrio(evento);
}

void CoordinadorPartidas::manejar(EventoFrenar& e) {
    uint32_t uuidJugador = e.uuidRemitente();
    uint16_t uuidPartida = jugadoresAPartidas_[uuidJugador];
    std::shared_ptr<Evento> evento = std::make_shared<EventoFrenar>(std::move(e));
    partidas_[uuidPartida]->ocurrio(evento);
}

void CoordinadorPartidas::manejar(EventoDejarDeFrenar& e) {
    uint32_t uuidJugador = e.uuidRemitente();
    uint16_t uuidPartida = jugadoresAPartidas_[uuidJugador];
    std::shared_ptr<Evento> evento = std::make_shared<EventoDejarDeFrenar>(std::move(e));
    partidas_[uuidPartida]->ocurrio(evento);
}

void CoordinadorPartidas::manejar(EventoDoblarIzquierda& e) {
    uint32_t uuidJugador = e.uuidRemitente();
    uint16_t uuidPartida = jugadoresAPartidas_[uuidJugador];
    std::shared_ptr<Evento> evento = std::make_shared<EventoDoblarIzquierda>(std::move(e));
    partidas_[uuidPartida]->ocurrio(evento);
}

void CoordinadorPartidas::manejar(EventoDejarDeDoblarIzquierda& e) {
    uint32_t uuidJugador = e.uuidRemitente();
    uint16_t uuidPartida = jugadoresAPartidas_[uuidJugador];
    std::shared_ptr<Evento> evento = std::make_shared<EventoDejarDeDoblarIzquierda>(std::move(e));
    partidas_[uuidPartida]->ocurrio(evento);
}

void CoordinadorPartidas::manejar(EventoDoblarDerecha& e) {
    uint32_t uuidJugador = e.uuidRemitente();
    uint16_t uuidPartida = jugadoresAPartidas_[uuidJugador];
    std::shared_ptr<Evento> evento = std::make_shared<EventoDoblarDerecha>(std::move(e));
    partidas_[uuidPartida]->ocurrio(evento);
}

void CoordinadorPartidas::manejar(EventoDejarDeDoblarDerecha& e) {
    uint32_t uuidJugador = e.uuidRemitente();
    uint16_t uuidPartida = jugadoresAPartidas_[uuidJugador];
    std::shared_ptr<Evento> evento = std::make_shared<EventoDejarDeDoblarDerecha>(std::move(e));
    partidas_[uuidPartida]->ocurrio(evento);
}
