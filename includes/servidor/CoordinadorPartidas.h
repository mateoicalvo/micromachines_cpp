#ifndef _COORDINADOR_PARTIDAS_H_
#define _COORDINADOR_PARTIDAS_H_

#include <map>
#include <memory>

#include "includes/servidor/Partida.h"
#include "includes/servidor/SalaDeEspera.h"
#include "includes/common/Handler.h"

class CoordinadorPartidas : public Handler{
private:
    uint16_t contadorPartidas_;
    SalaDeEspera& salaDeEspera_;
    std::map<uint16_t, std::shared_ptr<Partida>> partidas_;
    std::map<uint32_t, uint16_t> jugadoresAPartidas_;

public:
    CoordinadorPartidas(SalaDeEspera& salaDeEspera);
    ~CoordinadorPartidas();

    void agregarJugadorAPartida(std::shared_ptr<Jugador> jugador, uint16_t uuidPartida);

    std::shared_ptr<EventoSnapshotSala> getSnapshotSala();
    std::shared_ptr<EventoSnapshotLobby> getSnapshotLobby(uint16_t uuidPartida);

    virtual void manejar(Evento& e) override;
    virtual void manejar(EventoCrearPartida& e) override;
    virtual void manejar(EventoIniciarPartida& e) override;
    virtual void manejar(EventoDesconexion& e) override;
    virtual void manejar(EventoAcelerar& e) override;
    virtual void manejar(EventoDesacelerar& e) override;
    virtual void manejar(EventoFrenar& e) override;
    virtual void manejar(EventoDejarDeFrenar& e) override;
    virtual void manejar(EventoDoblarIzquierda& e) override;
    virtual void manejar(EventoDejarDeDoblarIzquierda& e) override;
    virtual void manejar(EventoDoblarDerecha& e) override;
    virtual void manejar(EventoDejarDeDoblarDerecha& e) override;
};

#endif

