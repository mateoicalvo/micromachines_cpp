#include <includes/cliente/GUI/AnimacionFactory.h>
#include "includes/cliente/GUI/Boton.h"

Boton::Boton(int uuid, Renderizador &renderizador, uint16_t x, uint16_t y) :
    x(x), y(y), animacion_(AnimacionFactory::instanciar(uuid, renderizador)) {}

Animacion &Boton::getAnimacion() {
  return this->animacion_;
}

bool Boton::estaSeleccionado(uint16_t x, uint16_t y) {
  return x >= this->x &&
      x <= (this->x + this->animacion_.ancho()) &&
      y >= this->y &&
      y <= (this->y + this->animacion_.alto());
}

uint16_t Boton::getX() const {
  return x;
}

uint16_t Boton::getY() const {
  return y;
}