#include "includes/servidor/modelo/fisicas/transformaciones/Reubicar.h"

#include "includes/3rd-party/Box2D/Box2D.h"
#include "includes/servidor/modelo/movimiento/Posicion.h"

#ifndef DEGTORAD
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#endif

Reubicar::Reubicar(Fisicas& fisicas, b2Body* cuerpo, Posicion& posicion) :
    Transformacion(fisicas),
    cuerpo_(cuerpo),
    posicion_(posicion) {

}

void Reubicar::aplicar() {
    cuerpo_->SetTransform(b2Vec2(posicion_.x_, posicion_.y_), (float)posicion_.anguloDeg_*DEGTORAD);
    cuerpo_->SetLinearVelocity(b2Vec2(0, 0));
    cuerpo_->SetAngularVelocity(0.0f);
}
