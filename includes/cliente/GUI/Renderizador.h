#ifndef _RENDERIZADOR_H_
#define _RENDERIZADOR_H_

#include "includes/cliente/GUI/Textura.h"
#include "includes/cliente/GUI/Texto.h"
#include "includes/cliente/utils/DobleBuffer.h"
#include <vector>

//Forward declarations:
class SDL_Renderer;
class Escena;
class Ventana;

#define SDL_PRIMER_DISPONIBLE -1

class Renderizador {
 private:
  SDL_Renderer *renderizadorSDL_;
  Ventana &ventana_;

  Renderizador(const Renderizador &) = delete;
  Renderizador &operator=(const Renderizador &) = delete;

 public:
  Renderizador(Ventana &ventana);
  ~Renderizador();
  void clear();
  void dibujar(uint32_t numeroIteracion, Escena &escena);
  void dibujar(uint32_t numeroIteracion, Escena &escena, DobleBuffer<std::vector<char>>& buffer);
  void setDestino(Textura &textura);
  void resetDestino();
  void dibujar(Textura &textura, Area &destino);
  void dibujarTexto(Texto &texto, Area &destino);
  void dibujar(Textura &textura, Area &destino, double grados, bool flipVertical);
  void toggleFullScreen();

  SDL_Renderer *getSDL();
};

#endif
