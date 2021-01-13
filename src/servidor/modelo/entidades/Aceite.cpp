#include "includes/servidor/modelo/entidades/Aceite.h"

Aceite::Aceite(uint8_t uuid) :
    Modificador(uuid) {
}

int Aceite::getTipo() {
    return ACEITE_;
}
