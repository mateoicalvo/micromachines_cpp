#include "includes/servidor/modelo/entidades/Barro.h"

Barro::Barro(uint8_t uuid) :
    Modificador(uuid) {
}

int Barro::getTipo() {
    return BARRO_;
}
