#ifndef _REUBICAR_H_
#define _REUBICAR_H_

#include "includes/servidor/modelo/fisicas/transformaciones/Transformacion.h"

#include "includes/servidor/modelo/Colisionable.h"

//Forward declarations
class b2Body;
class Posicion;

class Reubicar : public Transformacion {
private:
    b2Body* cuerpo_;
    Posicion& posicion_;
public:
    Reubicar(Fisicas& fiscas, b2Body* cuerpo, Posicion& posicion);
    virtual void aplicar() override;
};

#endif
