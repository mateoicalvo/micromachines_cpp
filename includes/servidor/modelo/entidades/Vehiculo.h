#ifndef _VEHICULO_H_
#define _VEHICULO_H_

#include <vector>

#include "includes/servidor/modelo/Identificable.h"
#include "includes/servidor/modelo/Colisionable.h"
#include "includes/servidor/modelo/movimiento/Posicion.h"
#include "includes/servidor/Jugador.h"

typedef struct futuro {
    std::shared_ptr<Evento> evento;
    uint32_t steps;
} futuro_t;

class Vehiculo : public Identificable, public Colisionable {
private:
    unsigned int velocidadMaximaAdelante_;
    unsigned int velocidadMaximaAtras_;
    unsigned int aceleracion_;
    unsigned int maniobrabilidad_;
    unsigned int agarre_;
    unsigned int salud_;
    unsigned int saludDefault_;
    Posicion respawn_;
    std::shared_ptr<Jugador> duenio_;
    std::vector<futuro_t> futuros_;
    
public:
    Vehiculo(uint8_t uuid,
            unsigned int velocidadMaximaAdelante,
            unsigned int velocidadMaximaAtras,
            unsigned int aceleracion,
            unsigned int maniobrabilidad,
            unsigned int agarre,
            unsigned int salud,
            Posicion respawn,
            std::shared_ptr<Jugador> duenio);

    unsigned int velocidadMaximaAdelante();
    unsigned int velocidadMaximaAtras();
    unsigned int aceleracion();
    unsigned int maniobrabilidad();
    unsigned int agarre();
    unsigned int salud();

    std::shared_ptr<Jugador> duenio();

    void step();

    void ocurrira(std::shared_ptr<Evento> unEvento, uint32_t steps);

    bool disminuirSalud(uint8_t cantidad);
    void sumarSalud(int delta);

    virtual int getTipo() override;
    Posicion& getPuntoRespawn();
    void setPuntoRespawn(Posicion& Posicion);
};

#endif
