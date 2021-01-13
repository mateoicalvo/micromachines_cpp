#ifndef _CHECKPOINT_H_
#define _CHECKPOINT_H_

#include "includes/servidor/modelo/Colisionable.h"
#include "includes/servidor/modelo/movimiento/Posicion.h"

//Forward declarations
class Carrera;
class Vehiculo;

class Checkpoint : public Colisionable {
private:
    Carrera& carrera_;
    int id_;
    int idDelSiguiente_;
    float ancho_;
    float alto_;
    Posicion puntoRespawn_;

public:
    Checkpoint(Carrera& carrera, int id, int idDelSiguiente, float ancho, float alto, Posicion& posicion);    
    virtual ~Checkpoint();
    virtual int getTipo() override;
    Posicion& posicion();
    float ancho();
    float alto();
    void registrarPaso(Vehiculo& vehiculo);
    int id();
};

#endif
