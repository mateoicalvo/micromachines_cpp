#ifndef _FISICAS_H_
#define _FISICAS_H_

#include <map>
#include <memory>

#include "includes/3rd-party/Box2D/Box2D.h"
#include "includes/common/Tile.h"
#include "includes/common/Cola.h"
#include "includes/common/eventos/Evento.h"
#include "includes/servidor/modelo/superficies/Superficie.h"
#include "includes/servidor/modelo/entidades/Vehiculo.h"
#include "includes/servidor/modelo/entidades/carrera/Checkpoint.h"
#include "includes/servidor/modelo/entidades/Modificador.h"
#include "includes/servidor/modelo/movimiento/Posicion.h"
#include "includes/servidor/modelo/fisicas/B2DVehiculo.h"
#include "includes/servidor/modelo/fisicas/ContactListener.h"
#include "includes/servidor/modelo/fisicas/transformaciones/Transformacion.h"

#ifndef DEGTORAD
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#endif

//FD
class Mundo;

class Fisicas {
private:
    b2Vec2 gravedad_;
    std::shared_ptr<b2World> mundoBox2D_;
    std::map<uint8_t, b2Body*> colisionables_;
    std::map<uint8_t, std::shared_ptr<B2DVehiculo>> vehiculos_;
    double frecuencia_;
    uint32_t iteracion_;
    Cola<std::shared_ptr<Evento>>& eventosOcurridos_;
    std::queue<std::shared_ptr<Transformacion>> transformaciones_;
    Mundo& mundo_;
    
public:
    Fisicas(Cola<std::shared_ptr<Evento>>& eventosOcurridos, ContactListener& contactListener, Mundo& mundo);
    ~Fisicas();
    void generarSuelo(std::map<Tile, std::shared_ptr<Superficie>>& tileASuelo);
    //void generarSuperficies(std::map<Tile, std::shared_ptr<Superficie>>& tileASuperficie);
    void generarCheckpoints(std::map<int, Checkpoint>& checkpoints);
    void step(uint32_t numeroIteracion);
    
    void agregarVehiculo(Vehiculo& vehiculo, Posicion& posicion);
    void acelerar(uint8_t uuidVehiculo);
    void desacelerar(uint8_t uuidVehiculo);
    void frenar(uint8_t uuidVehiculo);
    void dejarDeFrenar(uint8_t uuidVehiculo);
    void doblarIzquierda(uint8_t uuidVehiculo);
    void dejarDeDoblarIzquierda(uint8_t uuidVehiculo);
    void doblarDerecha(uint8_t uuidVehiculo);
    void dejarDeDoblarDerecha(uint8_t uuidVehiculo);

    void agregarModificador(std::shared_ptr<Modificador> modificador, uint8_t tipo, Posicion& posicion);

    void ocurrio(std::shared_ptr<Evento> evento);
    
    Posicion getPosicionDe(uint8_t idCuerpo);
    void nuevoUuidDisponible(uint8_t uuid);
    
    void reubicar(Vehiculo& vehiculo, Posicion& Posicion);
    void quitar(CajaVida& cajaVida);
    void quitar(Barro& barro);
    void quitar(Aceite& aceite);
    void quitar(Boost& boost);
    void quitar(Piedra& piedra);

};

#endif
