#include "includes/cliente/GUI/Textura.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "includes/cliente/GUI/Renderizador.h"
#include "includes/cliente/excepciones/SDLException.h"

Textura::Textura(const std::string& rutaArchivo, Renderizador& renderizador) {
    
    texturaSDL_ = IMG_LoadTexture(renderizador.getSDL(), rutaArchivo.c_str());
    if (!texturaSDL_) {
        throw SDLException("Error al cargar la textura", SDL_GetError());
    }
}

Textura::Textura(Textura&& otraTextura) {
    this->texturaSDL_ = otraTextura.texturaSDL_;
    otraTextura.texturaSDL_ = nullptr;
}

Textura& Textura::operator=(Textura&& otraTextura) {
    this->texturaSDL_ = otraTextura.texturaSDL_;
    otraTextura.texturaSDL_ = nullptr;
    return *this;
}

Textura::Textura(Renderizador& renderizador, Area dimensiones) {
    texturaSDL_ = SDL_CreateTexture(renderizador.getSDL(),
        SDL_PIXELFORMAT_RGB24,
        SDL_TEXTUREACCESS_TARGET,
        dimensiones.ancho(),
        dimensiones.alto());
    if (!texturaSDL_) {
        throw SDLException("Error al crear textura vacía", SDL_GetError());
    }
    renderizador.clear();
}

Textura::~Textura() {
    if (texturaSDL_ != nullptr) {
        SDL_DestroyTexture(texturaSDL_);
    }    
}

SDL_Texture* Textura::getSDL() {
    return texturaSDL_;
}
