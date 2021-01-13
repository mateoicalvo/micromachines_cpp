#include "includes/servidor/modelo/entidades/CajaVida.h"

CajaVida::CajaVida(uint8_t uuid, int deltaVida) :
    Modificador(uuid),
    deltaVida_(deltaVida) {

}

int CajaVida::getTipo() {
    return SALUD_;
}

int CajaVida::deltaVida() {
    return deltaVida_;
}