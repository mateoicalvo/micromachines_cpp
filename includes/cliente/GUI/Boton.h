#ifndef _BOTON_H_
#define _BOTON_H_

#include "includes/cliente/GUI/Animacion.h"
class Boton {
 private:
  uint16_t x, y;
  Animacion animacion_;
 public:
  Boton(int uuid, Renderizador &renderizador, uint16_t x, uint16_t y);
  Animacion &getAnimacion();
  bool estaSeleccionado(uint16_t x, uint16_t y);
  uint16_t getX() const;
  uint16_t getY() const;
};
#endif
