#ifndef _TEXTURA_H_
#define _TEXTURA_H_

#include <string>

#include "includes/cliente/GUI/Area.h"

// Forward Declarations:
class SDL_Texture;

class Renderizador;

class Textura {
 protected:
  SDL_Texture *texturaSDL_;
 private:
  Textura(const Textura &) = delete;
  Textura &operator=(const Textura &) = delete;

 public:
  Textura(const std::string &rutaArchivo, Renderizador &renderizador);
  Textura(Renderizador &renderizador, Area dimensiones);
  Textura(Textura &&otraTextura);
  Textura &operator=(Textura &&otraTextura);
  ~Textura();

  SDL_Texture *getSDL();
};

#endif
