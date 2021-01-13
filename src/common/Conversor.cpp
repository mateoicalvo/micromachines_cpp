#include "includes/common/Conversor.h"
#include <math.h>

Conversor::Conversor(float pixelPorMetro, int pixelPorBloque) :
    pixelPorMetro(pixelPorMetro), pixelPorBloque(pixelPorBloque) {}

int Conversor::metroAPixel(float coord) {
  return round(coord * pixelPorMetro);
}

float Conversor::pixelAMetro(int coord) {
  return (float) (coord / pixelPorMetro);
}

int Conversor::bloqueAPixel(int coord) {
  return coord * pixelPorBloque;
}

int Conversor::pixelABloque(int coord) {
  return trunc((float) coord / pixelPorBloque);
}
