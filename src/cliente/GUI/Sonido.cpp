#include "includes/cliente/GUI/Sonido.h"

#include "includes/cliente/excepciones/SDLException.h"

Sonido::Sonido(std::string filename,bool loop): loop(loop) {
  if (SDL_Init(SDL_INIT_AUDIO) < 0) {
    throw SDLException("Error al iniciar audio con SDL", SDL_GetError());
  }
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    throw SDLException("Error al iniciar audio con mixer", SDL_GetError());
  }
  this->efectoSonido = Mix_LoadWAV(filename.c_str());
  if (!this->efectoSonido) {
    throw SDLException("Error cargando sonido. ", Mix_GetError());
  }
}

void Sonido::setVolume(int volume) {
  this->efectoSonido->volume = volume;
}

void Sonido::play() {
  Mix_PlayChannel(-1, this->efectoSonido, -1 * loop);
}

void Sonido::stop() {
  Mix_HaltChannel(-1);
}

Sonido::~Sonido() {
  if (this->efectoSonido != NULL)
    Mix_FreeChunk(this->efectoSonido);
  Mix_CloseAudio();
  SDL_QuitSubSystem(SDL_INIT_AUDIO);
}