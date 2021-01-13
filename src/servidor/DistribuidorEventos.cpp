#include "includes/servidor/DistribuidorEventos.h"

DistribuidorEventos::DistribuidorEventos(ColaBloqueante<std::shared_ptr<Evento>>& eventos, SalaDeEspera& salaDeEspera, CoordinadorPartidas& coordinadorPartidas) :
    eventos_(eventos),
    salaDeEspera_(salaDeEspera),
    coordinadorPartidas_(coordinadorPartidas) {
}

DistribuidorEventos::~DistribuidorEventos() {
}

void DistribuidorEventos::correr() {
    bool obtenido;
    std::shared_ptr<Evento> evento;
    while(seguirCorriendo_ && (obtenido = eventos_.get(evento))) {
        manejar(*evento);
    }
}

void DistribuidorEventos::detener() {
    seguirCorriendo_ = false;
}

void DistribuidorEventos::manejar(Evento& e) {
    e.actualizar(*this);
}

void DistribuidorEventos::manejar(EventoAcelerar& e) {
    coordinadorPartidas_.manejar(e);
}

void DistribuidorEventos::manejar(EventoDesacelerar& e) {
    coordinadorPartidas_.manejar(e);
}

void DistribuidorEventos::manejar(EventoFrenar& e) {
    coordinadorPartidas_.manejar(e);
}

void DistribuidorEventos::manejar(EventoDejarDeFrenar& e) {
    coordinadorPartidas_.manejar(e);
}

void DistribuidorEventos::manejar(EventoDoblarIzquierda& e) {
    coordinadorPartidas_.manejar(e);
}

void DistribuidorEventos::manejar(EventoDejarDeDoblarIzquierda& e) {
    coordinadorPartidas_.manejar(e);
}

void DistribuidorEventos::manejar(EventoDoblarDerecha& e) {
    coordinadorPartidas_.manejar(e);
}

void DistribuidorEventos::manejar(EventoDejarDeDoblarDerecha& e) {
    coordinadorPartidas_.manejar(e);
}

void DistribuidorEventos::manejar(EventoCrearPartida& e) {
    coordinadorPartidas_.manejar(e);
}

void DistribuidorEventos::manejar(EventoUnirseAPartida& e) {
    uint32_t uuidJugador = e.uuidRemitente();
    uint16_t uuidPartida = e.uuidPartida_;
    std::shared_ptr<Jugador> jugador = salaDeEspera_.quitarJugador(uuidJugador);
    coordinadorPartidas_.agregarJugadorAPartida(jugador, uuidPartida);
}

void DistribuidorEventos::manejar(EventoDesconexion& e) {
    salaDeEspera_.manejar(e);
    coordinadorPartidas_.manejar(e);
}

void DistribuidorEventos::manejar(EventoIniciarPartida& e) {
    coordinadorPartidas_.manejar(e);   
}

void DistribuidorEventos::manejar(EventoUnirseASala& e) {
    std::shared_ptr<EventoSnapshotSala> snapshot = coordinadorPartidas_.getSnapshotSala();
    snapshot->setRemitente(e.uuidRemitente());
    salaDeEspera_.ocurrio(snapshot);
}
