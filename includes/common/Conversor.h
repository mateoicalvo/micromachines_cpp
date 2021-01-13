#ifndef _CONVERSOR_H_
#define _CONVERSOR_H_

/*
 * Conversor que realiza el traspaso
 * de metros a pixeles y a bloques
 */
class
Conversor {
 private:
  float pixelPorMetro;
  int pixelPorBloque;

 public:
  Conversor(float pixelPorMetro, int pixelPorBloque);
  int metroAPixel(float coord);
  float pixelAMetro(int coord);
  int bloqueAPixel(int coord);
  int pixelABloque(int coord);
  //TODO: Refactor this
  static float tileAMetro(float coordenada) {
    return 10.0f * coordenada;
  }
  
};
#endif
