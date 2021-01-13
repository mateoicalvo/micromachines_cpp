#include "includes/servidor/modelo/fisicas/ContactListener.h"

#include "includes/servidor/modelo/Colisionable.h"
#include "includes/servidor/utils/ConfigServidor.h"

#include "includes/servidor/modelo/entidades/carrera/Checkpoint.h"
#include "includes/servidor/modelo/superficies/SuperficieArena.h"
#include "includes/servidor/modelo/entidades/Vehiculo.h"
#include "includes/servidor/modelo/entidades/CajaVida.h"
#include "includes/servidor/modelo/entidades/Aceite.h"
#include "includes/servidor/modelo/entidades/Barro.h"
#include "includes/servidor/modelo/entidades/Piedra.h"
#include "includes/servidor/modelo/entidades/Boost.h"
#include "includes/servidor/modelo/fisicas/Fisicas.h"

#include "includes/common/eventos/EventoChoque.h"
#include "includes/common/eventos/EventoExplosion.h"
#include "includes/common/eventos/EventoBarroPisado.h"
#include "includes/common/eventos/EventoFinBarro.h"

// Métodos privados
static void ordenar(Colisionable** A, Colisionable** B);

ContactListener::ContactListener(Fisicas& fisicas) :
    fisicas_(fisicas) {
}

ContactListener::~ContactListener() {    
}
#include <iostream>
void ContactListener::BeginContact(b2Contact* contact) {
    //Son raw pointers pero b2d garantiza que no se eliminan ni agregan cuerpos durante
    // las colisiones
    Colisionable* colisionableA = contact->GetFixtureA()->GetBody()->GetUserData();
    Colisionable* colisionableB = contact->GetFixtureB()->GetBody()->GetUserData();

    ordenar(&colisionableA, &colisionableB);

    // No debería ocurrir porque no le puse data a los fixtures.
    //if(!colisionableA || !colisionableB) {
    //    return;
    //}

    if (colisionableA->getTipo() == Colisionable::tipos::VEHICULO_) {
        if (colisionableB->yaFueColisionado()) {
            //No queremos eliminar dos veces o revienta todo
            return;
        }
        if (colisionableB->getTipo() == Colisionable::tipos::VEHICULO_) {
            vehiculoVsVehiculo(*static_cast<Vehiculo*>(colisionableA), *static_cast<Vehiculo*>(colisionableB));
        }
        if (colisionableB->getTipo() == Colisionable::tipos::SUPERFICIE_ARENA_) {
            vehiculoVsArena(*static_cast<Vehiculo*>(colisionableA), *static_cast<SuperficieArena*>(colisionableB));
        }
        if (colisionableB->getTipo() == Colisionable::tipos::CHECKPOINT_) {
            vehiculoVsCheckpoint(*static_cast<Vehiculo*>(colisionableA), *static_cast<Checkpoint*>(colisionableB));
        }
        if (colisionableB->getTipo() == Colisionable::tipos::SUPERFICIE_TIERRA_) {
            //TODO: No se pueden modificar valores acá, hay que obtener el b2Vehiculo
        }
        if (colisionableB->getTipo() == Colisionable::tipos::SUPERFICIE_PISTA_) {
        }
        if (colisionableB->getTipo() == Colisionable::tipos::SALUD_) {
            vehiculoVsCajaVida(*static_cast<Vehiculo*>(colisionableA), *static_cast<CajaVida*>(colisionableB));
        }
        if (colisionableB->getTipo() == Colisionable::tipos::ACEITE_) {
            vehiculoVsAceite(*static_cast<Vehiculo*>(colisionableA), *static_cast<Aceite*>(colisionableB));
        }
        if (colisionableB->getTipo() == Colisionable::tipos::BARRO_) {
            vehiculoVsBarro(*static_cast<Vehiculo*>(colisionableA), *static_cast<Barro*>(colisionableB));
        }
        if (colisionableB->getTipo() == Colisionable::tipos::PIEDRA_) {
            vehiculoVsPiedra(*static_cast<Vehiculo*>(colisionableA), *static_cast<Piedra*>(colisionableB));
        }
        if (colisionableB->getTipo() == Colisionable::tipos::BOOST_) {
            vehiculoVsBoost(*static_cast<Vehiculo*>(colisionableA), *static_cast<Boost*>(colisionableB));
        }
    }
}

void ContactListener::EndContact(b2Contact* contact) {
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
    /*b2WorldManifold worldManifold;
    contact->GetWorldManifold(&worldManifold);
    b2PointState state1[2], state2[2];
    b2GetPointStates(state1, state2, oldManifold, contact->GetManifold());
    if (state2[0] == b2_addState) {
        const b2Body* bodyA = contact->GetFixtureA()->GetBody();
        const b2Body* bodyB = contact->GetFixtureB()->GetBody();
        b2Vec2 point = worldManifold.points[0];
        b2Vec2 vA = bodyA->GetLinearVelocityFromWorldPoint(point);
        b2Vec2 vB = bodyB->GetLinearVelocityFromWorldPoint(point);
        float32 approachVelocity = b2Dot(vB -vA, worldManifold.normal);    */        
}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {
    
}

static void ordenar(Colisionable** A, Colisionable** B) {
    
    Colisionable* Aptr = *A;
    Colisionable* Bptr = *B;
    
    int tipoDeA = Aptr->getTipo();
    int tipoDeB = Bptr->getTipo();

    if (tipoDeB < tipoDeA) {
        Colisionable* tmp = *B;
        *B = *A;
        *A = tmp;
    }
}

void ContactListener::vehiculoVsArena(Vehiculo& vehiculo, SuperficieArena& arena) {
    Posicion posicionVehiculo = fisicas_.getPosicionDe(vehiculo.uuid());
    std::shared_ptr<Evento> explosion = std::make_shared<EventoExplosion>(posicionVehiculo.x_, posicionVehiculo.y_);
    fisicas_.ocurrio(explosion);
    fisicas_.reubicar(vehiculo, vehiculo.getPuntoRespawn());
}

void ContactListener::vehiculoVsCheckpoint(Vehiculo& vehiculo, Checkpoint& checkpoint) {
   checkpoint.registrarPaso(vehiculo);
}

void ContactListener::vehiculoVsVehiculo(Vehiculo& vehiculoA, Vehiculo& vehiculoB) {
    Posicion posicionVehiculoA = fisicas_.getPosicionDe(vehiculoA.uuid());
    std::shared_ptr<Evento> choque = std::make_shared<EventoChoque>(posicionVehiculoA.x_, posicionVehiculoA.y_);
    fisicas_.ocurrio(choque);

    uint8_t disminucionVida = CONFIG_SERVIDOR.disminucionVidaChoqueConVehiculo();
    bool vehiculoAExploto = vehiculoA.disminuirSalud(disminucionVida);
    if (vehiculoAExploto) {
        std::shared_ptr<Evento> explosion = std::make_shared<EventoExplosion>(posicionVehiculoA.x_, posicionVehiculoA.y_);
        fisicas_.ocurrio(explosion);
        fisicas_.reubicar(vehiculoA, vehiculoA.getPuntoRespawn());
    }
    bool vehiculoBExploto = vehiculoB.disminuirSalud(disminucionVida);
    if (vehiculoBExploto) {
        Posicion posicionVehiculoB = fisicas_.getPosicionDe(vehiculoB.uuid());
        std::shared_ptr<Evento> explosion = std::make_shared<EventoExplosion>(posicionVehiculoB.x_, posicionVehiculoB.y_);
        fisicas_.ocurrio(explosion);
        fisicas_.reubicar(vehiculoB, vehiculoB.getPuntoRespawn());
    }
}

void ContactListener::vehiculoVsCajaVida(Vehiculo& vehiculo, CajaVida& cajaVida) {
    int deltaVida = cajaVida.deltaVida();
    vehiculo.sumarSalud(deltaVida);
    fisicas_.quitar(cajaVida);
}

void ContactListener::vehiculoVsAceite(Vehiculo& vehiculo, Aceite& aceite) {
    fisicas_.quitar(aceite);
}

void ContactListener::vehiculoVsBarro(Vehiculo& vehiculo, Barro& barro) {
    std::shared_ptr<Evento> pisoBarro = std::make_shared<EventoBarroPisado>();
    fisicas_.quitar(barro);
    vehiculo.duenio()->ocurrio(pisoBarro);
    std::shared_ptr<Evento> noMasBarro = std::make_shared<EventoFinBarro>();
    //TODO: No hardcodear
    vehiculo.ocurrira(noMasBarro, 300);
}

void ContactListener::vehiculoVsBoost(Vehiculo& vehiculo, Boost& boost) {
    fisicas_.quitar(boost);
}

void ContactListener::vehiculoVsPiedra(Vehiculo& vehiculo, Piedra& piedra) {
    //TODO: NO HARDCODEAR
    bool exploto = vehiculo.disminuirSalud(30);
    if (exploto) {
        Posicion posicionVehiculo = fisicas_.getPosicionDe(vehiculo.uuid());
        std::shared_ptr<Evento> explosion = std::make_shared<EventoExplosion>(posicionVehiculo.x_, posicionVehiculo.y_);
        fisicas_.ocurrio(explosion);
        fisicas_.reubicar(vehiculo, vehiculo.getPuntoRespawn());
    }
    fisicas_.quitar(piedra);
    
}