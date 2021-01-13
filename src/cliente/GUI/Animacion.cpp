#include <iostream>
#include "includes/cliente/GUI/Animacion.h"
#include "includes/cliente/utils/ConfigCliente.h"

void Animacion::loadFramesByIteration() {
  int frames_division = iterations_.size() / frames_.size();
  int frame_selected = 0;
  int frame = 0;
  for (size_t i = 0 ;i <iterations_.size();i++){
    if (frame > frames_division) {
      frame = 0;
      frame_selected++;
    }
    iterations_[i] = frame_selected;
    frame ++;
  }
}

Animacion::Animacion(std::vector<Textura> &texturas, unsigned int ancho, unsigned int alto) :
    ancho_(ancho),
    alto_(alto),
    iterations_(CONFIG_CLIENTE.fps(), 0) {
  this->primerIteracion = false;
  for (Textura &t : texturas) {
    frames_.push_back(std::move(t));
  }
  loadFramesByIteration();
}

Textura &Animacion::get(uint32_t numeroIteracion) {
  int resto = numeroIteracion % iterations_.size();
  if (numeroIteracion != 0 && resto == 0){
    primerIteracion = true;
  }
  return frames_[iterations_[resto]];
}

bool Animacion::terminoPrimerIteracion() const {
  return primerIteracion;
}

unsigned int Animacion::ancho() {
  return ancho_;
}
unsigned int Animacion::alto() {
  return alto_;
}
