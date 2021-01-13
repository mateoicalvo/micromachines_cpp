#include "includes/servidor/modelo/Identificable.h"

Identificable::Identificable(uint8_t uuid) :
    UUID_(uuid) {
}

Identificable::~Identificable() {
}

uint8_t Identificable::uuid() {
    return UUID_;
}
