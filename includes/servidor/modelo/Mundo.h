#ifndef _MUNDO_H_
#define _MUNDO_H_

#include <memory>
#include <queue>

#include "includes/common/Handler.h"
#include "includes/common/ColaProtegida.h"
#include "includes/servidor/modelo/fisicas/Fisicas.h"
#include "includes/servidor/modelo/fisicas/ContactListener.h"
#include "includes/servidor/modelo/entidades/Vehiculo.h"
#include "includes/servidor/modelo/entidades/Modificador.h"
#include "includes/common/Tile.h"
#include "includes/servidor/modelo/superficies/Superficie.h"
#include "includes/servidor/modelo/entidades/carrera/Carrera.h"
#include "includes/servidor/Jugador.h"

class Mundo : public Handler {
private:
    std::map<Tile, std::shared_ptr<Superficie>> tileASuelo_;
    std::vector<Tile> tilesConPista_;
    std::queue<Posicion> posicionesIniciales_;
    std::map<uint32_t, Vehiculo> jugadoresAVehiculos_;
    ColaProtegida<std::shared_ptr<Evento>> eventosOcurridos_;
    Fisicas fisicas_;    
    std::queue<uint8_t> uuidsObjetos_;
    std::map<uint32_t, uint8_t> jugadoresAIDVehiculo_;
    unsigned int snapshotsEnviadosPorSegundo_;
    ContactListener contactListener_;
    Carrera carrera_;
    std::map<uint8_t, std::shared_ptr<Modificador>> modificadores_;

    std::map<uint8_t, datosVehiculo_> serializarEstado();

public:
    Mundo(uint16_t uuidPista);
    ~Mundo();

    void step(uint32_t numeroIteracion);
    Cola<std::shared_ptr<Evento>>& eventosOcurridos();
    uint8_t agregarVehiculo(std::shared_ptr<Jugador> unJugador);
    std::map<uint8_t, datosVehiculo_> getEstadoInicial();
    void agregarModificadores(uint32_t numeroIteracion);
    
    void recuperarUuid(uint8_t uuid);

    virtual void manejar(Evento& e) override;
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
