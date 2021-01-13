#ifndef _OBJETO_DINAMICO_H_
#define _OBJETO_DINAMICO_H_
#include "includes/cliente/GUI/AnimacionFactory.h"
#include "includes/cliente/GUI/Animacion.h"
#include "includes/cliente/GUI/Renderizador.h"
#include "includes/cliente/GUI/Sonido.h"

class ObjetoDinamico {
 private:
  uint16_t x, y, angulo, vida;
  Animacion animacion_;
  Sonido sonido;

 public:
  ObjetoDinamico(int uuid,
                 Renderizador &renderizador,
                 std::string sonido, bool loopSonido);
  Animacion &getAnimacion();
  void mover(uint16_t x, uint16_t y, uint16_t angulo);
  void setVida(uint16_t vida);
  uint16_t getX() const;
  uint16_t getY() const;
  uint16_t getAngulo() const;
  uint16_t getVida() const;
  Sonido &getSonido();
};
#endif
