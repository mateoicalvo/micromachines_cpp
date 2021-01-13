#include "includes/servidor/modelo/entidades/Vehiculo.h"

#include <algorithm>

Vehiculo::Vehiculo(uint8_t uuid,
            unsigned int velocidadMaximaAdelante,
            unsigned int velocidadMaximaAtras,
            unsigned int aceleracion,
            unsigned int maniobrabilidad,
            unsigned int agarre,
            //FIXME: CAMBIAR SALUD A UINT8T
            unsigned int salud,
            Posicion respawn,
            std::shared_ptr<Jugador> duenio) :
            Identificable(uuid),
            velocidadMaximaAdelante_(velocidadMaximaAdelante),
            velocidadMaximaAtras_(velocidadMaximaAtras),
            aceleracion_(aceleracion),
            maniobrabilidad_(maniobrabilidad),
            agarre_(agarre),
            salud_(salud),
            saludDefault_(salud),
            respawn_(respawn),
            duenio_(duenio) {
}

unsigned int Vehiculo::velocidadMaximaAdelante() {
    return velocidadMaximaAdelante_;
}

unsigned int Vehiculo::velocidadMaximaAtras() {
    return velocidadMaximaAtras_;
}

unsigned int Vehiculo::aceleracion() {
    return aceleracion_;
}

unsigned int Vehiculo::maniobrabilidad() {
    return maniobrabilidad_;
}

unsigned int Vehiculo::agarre() {
    return agarre_;
}

unsigned int Vehiculo::salud() {
    return salud_;
}

std::shared_ptr<Jugador> Vehiculo::duenio() {
    return duenio_;
}

void Vehiculo::ocurrira(std::shared_ptr<Evento> unEvento, uint32_t steps) {
    futuros_.push_back(futuro_t{unEvento, steps});
}

static bool termino(futuro_t& futuro) {
    return (futuro.steps == 0) && (futuro.evento.use_count() > 2);
}

void Vehiculo::step() {
    std::remove_if(futuros_.begin(), futuros_.end(), termino);
    for (auto& futuro : futuros_) {
        futuro.steps--;
        if (futuro.steps == 0) {
            duenio_->ocurrio(futuro.evento);
        }   
    }    
}

bool Vehiculo::disminuirSalud(uint8_t cantidad) {
    int saludFinal = salud_ - cantidad;
    if (saludFinal <= 0) {
        salud_ = saludDefault_;
        return true;
    }
    salud_ = saludFinal;
    return false;
}

void Vehiculo::sumarSalud(int delta) {
    unsigned int saludFinal = salud_ + delta;
    if (saludFinal > saludDefault_) {
        salud_ = saludDefault_;
    } else {
        salud_ = saludFinal;
    }
}

int Vehiculo::getTipo() {
    return VEHICULO_;
}

Posicion& Vehiculo::getPuntoRespawn() {
    return respawn_;
}

void Vehiculo::setPuntoRespawn(Posicion& posicion) {
    respawn_ = posicion;
}
