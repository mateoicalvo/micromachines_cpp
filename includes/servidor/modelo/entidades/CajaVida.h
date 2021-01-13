#ifndef _CAJA_VIDA_H_
#define _CAJA_VIDA_H_

#include "includes/servidor/modelo/entidades/Modificador.h"

class CajaVida : public Modificador {
private:
    int deltaVida_;
public:
    CajaVida(uint8_t uuid, int deltaVida);
    virtual int getTipo() override;
    int deltaVida();
};

#endif
