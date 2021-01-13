#ifndef _B2D_VEHICULO_H_
#define _B2D_VEHICULO_H_

#include <cstdint>

#include "includes/3rd-party/Box2D/Box2D.h"

#define DENSIDAD 0.05f
#define MAX_IMPULSO_LATERAL 15.0f
#define CORRECCION_DERRAPE 0.03f
#define AJUSTE_VOLANTE 2.5f
#define AJUSTE_VELOCIDAD 0.45f
#define AJUSTE_ACELERACION 0.25f

//Forward declarations
class b2Body;
class b2World;
class Vehiculo;

class B2DVehiculo {
private:
    static const int volanteIzquierda_ = 0x1;
    static const int volanteDerecha_ = 0x2;
    static const int acelerador_ = 0x4;
    static const int freno_ = 0x8;
    int control_;

    b2Body* cuerpoBox2D_;

    float velocidadMaxAdelante_;
    float velocidadMaxAtras_;
    // Fuerza que se aplica para acelerar/frenar el auto
    float fuerzaManejoMaxima_;
    // AKA rozamiento, agarre
    float traccion_;

public:
    B2DVehiculo(b2World* mundoBox2D, Vehiculo& vehiculo);
    ~B2DVehiculo();
    b2Vec2 getVelocidadLateral();
    b2Vec2 getVelocidadFrontal();
    b2Body* getB2D();
    void actualizarFriccion();
    void actualizarAceleracion();
    void actualizarVolante();
    void step();
    void acelerando();
    void desacelerando();
    void frenando();
    void dejandoDeFrenar();
    void doblandoIzquierda();
    void dejandoDeDoblarIzquierda();
    void doblandoDerecha();
    void dejandoDeDoblarDerecha();
};

#endif
