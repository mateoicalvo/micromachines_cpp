#include "includes/cliente/GUI/ObjetoDinamico.h"

ObjetoDinamico::ObjetoDinamico(int uuid,
                               Renderizador &renderizador,
                               std::string sonido,
                               bool loopSonido) :
    animacion_(AnimacionFactory::instanciar(uuid, renderizador)), sonido(sonido,loopSonido) {
  this->x = 0;
  this->y = 0;
  this->angulo = 0;
  this->vida = 100;
  this->sonido.setVolume(0);
  this->sonido.play();
}

Animacion &ObjetoDinamico::getAnimacion() {
  return this->animacion_;
}

void ObjetoDinamico::mover(uint16_t x, uint16_t y, uint16_t angulo) {
  this->x = x;
  this->y = y;
  this->angulo = angulo;
}

uint16_t ObjetoDinamico::getX() const {
  return this->x;
}

uint16_t ObjetoDinamico::getY() const {
  return this->y;
}

uint16_t ObjetoDinamico::getAngulo() const {
  return this->angulo;
}

void ObjetoDinamico::setVida(uint16_t vida) {
  this->vida = vida;
}

uint16_t ObjetoDinamico::getVida() const {
  return this->vida;
}

Sonido &ObjetoDinamico::getSonido() {
  return this->sonido;
}