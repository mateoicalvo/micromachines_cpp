#include "includes/servidor/modelo/entidades/carrera/Checkpoint.h"

#include "includes/servidor/modelo/entidades/carrera/Carrera.h"
#include "includes/servidor/modelo/entidades/Vehiculo.h"

Checkpoint::Checkpoint(Carrera& carrera, int id, int idDelSiguiente, float ancho, float alto, Posicion& posicion) :
    carrera_(carrera),
    id_(id),
    idDelSiguiente_(idDelSiguiente),
    ancho_(ancho),
    alto_(alto),
    puntoRespawn_(posicion) {
}

Checkpoint::~Checkpoint() {

}

int Checkpoint::getTipo() {
    return CHECKPOINT_;
}

Posicion& Checkpoint::posicion() {
    return puntoRespawn_;
}

float Checkpoint::ancho() {
    return ancho_;
}
float Checkpoint::alto() {
    return alto_;
}

int Checkpoint::id() {
    return id_;
}

void Checkpoint::registrarPaso(Vehiculo& vehiculo) {
    Checkpoint& ultimoCheckpoint = carrera_.ultimoCheckpointDe(vehiculo);
    if (ultimoCheckpoint.idDelSiguiente_ == id_) {
        //TODO: EN Meta será sumar vuelta
        vehiculo.setPuntoRespawn(puntoRespawn_);
        carrera_.setCheckpoint(vehiculo, *this);
    }
}
