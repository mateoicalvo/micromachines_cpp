#ifndef _ACEITE_H_
#define _ACEITE_H_

#include "includes/servidor/modelo/entidades/Modificador.h"

class Aceite : public Modificador {
public:
    Aceite(uint8_t uuid);
    virtual int getTipo() override;
};

#endif
