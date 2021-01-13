#include "includes/cliente/GUI/Renderizador.h"

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>

#include "includes/cliente/GUI/Ventana.h"
#include "includes/cliente/GUI/escenas/Escena.h"

Renderizador::Renderizador(Ventana &ventana) :
    ventana_(ventana) {
  renderizadorSDL_ = SDL_CreateRenderer(ventana.getSDL(),
                                        SDL_PRIMER_DISPONIBLE,
                                        SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
  clear();
}

Renderizador::~Renderizador() {
  SDL_DestroyRenderer(renderizadorSDL_);
}

void Renderizador::clear() {
  SDL_SetRenderDrawColor(renderizadorSDL_, 0x33, 0x33, 0x33, 0xFF);
  SDL_RenderClear(renderizadorSDL_);
}

void Renderizador::setDestino(Textura &textura) {
  SDL_SetRenderTarget(renderizadorSDL_, textura.getSDL());
  clear();
}

void Renderizador::resetDestino() {
  SDL_SetRenderTarget(renderizadorSDL_, NULL);
  clear();
}

void Renderizador::dibujar(Textura &textura, Area &area) {
  SDL_Rect SDLDestino = {
      (int) area.x(),
      (int) area.y(),
      (int) area.ancho(),
      (int) area.alto()
  };
  SDL_RenderCopy(renderizadorSDL_, textura.getSDL(), NULL, &SDLDestino);
}

void Renderizador::dibujarTexto(Texto &texto, Area &area) {
  SDL_Rect SDLDestino = {
      (int) area.x(),
      (int) area.y(),
      (int) area.ancho(),
      (int) area.alto()
  };
  SDL_RenderCopy(renderizadorSDL_, texto.getSDL(), NULL, &SDLDestino);
}


void Renderizador::dibujar(Textura &textura, Area &area, double grados, bool flipVertical) {
  SDL_Rect SDLDestino = {
      (int) area.x(),
      (int) area.y(),
      (int) area.ancho(),
      (int) area.alto()
  };
  if (flipVertical) {
    SDL_RenderCopyEx(renderizadorSDL_, textura.getSDL(), NULL, &SDLDestino, grados, NULL, SDL_FLIP_VERTICAL);
  } else {
    SDL_RenderCopyEx(renderizadorSDL_, textura.getSDL(), NULL, &SDLDestino, grados, NULL, SDL_FLIP_NONE);
  }
}

void Renderizador::dibujar(uint32_t numeroIteracion, Escena &escena) {
  Textura textura = escena.dibujate(numeroIteracion, ventana_.dimensiones());
  SDL_Rect SDLDestino = {
      0,
      0,
      (int) ventana_.ancho(),
      (int) ventana_.alto()};
  resetDestino();
  SDL_RenderCopy(renderizadorSDL_, textura.getSDL(), NULL, &SDLDestino);
  SDL_RenderPresent(renderizadorSDL_);
}

void Renderizador::dibujar(uint32_t numeroIteracion, Escena &escena, DobleBuffer<std::vector<char>>& buffer) {
  Textura textura = escena.dibujate(numeroIteracion, ventana_.dimensiones());
  SDL_Rect SDLDestino = {
      0,
      0,
      (int) ventana_.ancho(),
      (int) ventana_.alto()};  
  
  int anchoRGB = ventana_.ancho() * 3;
  std::vector<char> pixeles(anchoRGB * ventana_.alto());
  
  resetDestino();
  SDL_RenderCopy(renderizadorSDL_, textura.getSDL(), NULL, &SDLDestino);
  SDL_RenderReadPixels(renderizadorSDL_, NULL, SDL_PIXELFORMAT_RGB24, pixeles.data(), anchoRGB);
  buffer.set(std::move(pixeles));
  SDL_RenderPresent(renderizadorSDL_);
}

void Renderizador::toggleFullScreen() {
  ventana_.toggleFullScreen();
}

SDL_Renderer *Renderizador::getSDL() {
  return renderizadorSDL_;
}
