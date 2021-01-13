#include "includes/servidor/modelo/Colisionable.h"

Colisionable::~Colisionable() {
}

Colisionable::Colisionable() :
    yaColisionado_(false) {
}

void Colisionable::colisionado() {
    yaColisionado_ = true;
}

bool Colisionable::yaFueColisionado() {
    return yaColisionado_;
}
