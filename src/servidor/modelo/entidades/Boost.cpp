#include "includes/servidor/modelo/entidades/Boost.h"

Boost::Boost(uint8_t uuid) :
    Modificador(uuid) {
}

int Boost::getTipo() {
    return BOOST_;
}
