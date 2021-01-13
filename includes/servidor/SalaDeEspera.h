#ifndef _SALA_DE_ESPERA_H_
#define _SALA_DE_ESPERA_H_

#include <map>
#include <memory>
#include <mutex>

#include "includes/common/Handler.h"
#include "includes/common/red/SocketTCP.h"
#include "includes/servidor/Jugador.h"

class SalaDeEspera : public Handler {
private:
    uint32_t contadorJugadores_;
    ColaBloqueante<std::shared_ptr<Evento>>& destinoEventos_;
    //FIXME: Proteger esto
    std::map<uint32_t, std::shared_ptr<Jugador>> jugadores_;
    std::mutex mtx_;

public:
    SalaDeEspera(ColaBloqueante<std::shared_ptr<Evento>>& destinoEventos);
    ~SalaDeEspera();
    void agregarJugador(SocketTCP&& socket);
    void agregarJugador(std::shared_ptr<Jugador> unJugador);
    std::shared_ptr<Jugador> quitarJugador(uint32_t uuidJugador);
    std::shared_ptr<Jugador> getJugador(uint32_t uuidJugador);

    void ocurrio(std::shared_ptr<Evento> evento);

    virtual void manejar(Evento& e) override;
    virtual void manejar(EventoDesconexion& e) override;
};

#endif
