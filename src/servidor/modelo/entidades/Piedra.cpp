#include "includes/servidor/modelo/entidades/Piedra.h"

Piedra::Piedra(uint8_t uuid) :
    Modificador(uuid) {
}

int Piedra::getTipo() {
    return PIEDRA_;
}
