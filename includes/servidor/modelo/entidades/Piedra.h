#ifndef _PIEDRA_H_
#define _PIEDRA_H_

#include "includes/servidor/modelo/entidades/Modificador.h"

class Piedra : public Modificador {
public:
    Piedra(uint8_t uuid);
    virtual int getTipo() override;
};

#endif
