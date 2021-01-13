#ifndef _BOOST_H_
#define _BOOST_H_

#include "includes/servidor/modelo/entidades/Modificador.h"

class Boost : public Modificador {
public:
    Boost(uint8_t uuid);
    virtual int getTipo() override;
};

#endif
