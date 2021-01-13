#ifndef _MODIFICADOR_H_
#define _MODIFICADOR_H_

#include "includes/servidor/modelo/Colisionable.h"
#include "includes/servidor/modelo/Identificable.h"

class Modificador : public Colisionable, public Identificable {
public:
    Modificador(uint8_t uuid);
    virtual ~Modificador();
};

#endif
