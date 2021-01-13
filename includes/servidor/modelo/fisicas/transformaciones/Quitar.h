#ifndef _QUITAR_H_
#define _QUITAR_H_

#include "includes/servidor/modelo/fisicas/transformaciones/Transformacion.h"

#include <cstdint>

//Forward declarations
class b2Body;
class Fisicas;

class Quitar : public Transformacion {
private:
    b2Body* cuerpo_;
    uint8_t uuidCuerpo_;
public:
    Quitar(Fisicas& fiscas, b2Body* cuerpo, uint8_t uuidCuerpo);
    virtual void aplicar() override;
};

#endif
