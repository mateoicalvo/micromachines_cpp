#ifndef _BARRO_H_
#define _BARRO_H_

#include "includes/servidor/modelo/entidades/Modificador.h"

class Barro : public Modificador {
public:
    Barro(uint8_t uuid);
    virtual int getTipo() override;
};

#endif
