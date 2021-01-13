#include "includes/cliente/GUI/Texto.h"
#include "includes/cliente/utils/ConfigCliente.h"
#include "includes/cliente/excepciones/SDLException.h"
#include "includes/cliente/GUI/Renderizador.h"

SDL_Color Texto::getColorRGB(int uuidColor) {
  switch (uuidColor) {
    case UUID_TEXTO_BLANCO:return {255, 255, 255}; break;
    case UUID_TEXTO_NEGRO:return {0, 0, 0}; break;
    case UUID_TEXTO_ROJO:return {255, 0, 0}; break;
    case UUID_TEXTO_AMARILLO:return {255, 255, 0}; break;
    case UUID_TEXTO_VERDE: return {0, 255, 0}; break;
    default:return {255, 255, 255};
  }
}

SDL_Texture *Texto::createFromText(const std::string texto,
                                   Renderizador &renderizador,
                                   int uuidColor) {
  SDL_Surface
      *surface =
      TTF_RenderText_Blended(this->font, texto.c_str(), getColorRGB(uuidColor));
  if (!surface)
    throw SDLException("Error con TTF_RenderText_Blended:", SDL_GetError());
  SDL_Texture
      *texture = SDL_CreateTextureFromSurface(renderizador.getSDL(), surface);
  if (!texture) {
    throw SDLException("Error al cargar la textura", SDL_GetError());
  }
  SDL_FreeSurface(surface);
  return texture;
}

Texto::Texto(const std::string texto,
             const int size,
             Renderizador &renderizador, int uuidColor) {
  if (TTF_Init() == -1)
    throw SDLException("Error al iniciar TTF:", SDL_GetError());
  this->font = TTF_OpenFont(CONFIG_CLIENTE.fuente().c_str(), size);
  if (font == NULL)
    throw SDLException("Error al cargar font:", SDL_GetError());
  this->texturaSDL_ = createFromText(texto, renderizador, uuidColor);
}

SDL_Texture *Texto::getSDL() {
  return texturaSDL_;
}

void Texto::setColor(int uuidColor) {
  SDL_Color color = getColorRGB(uuidColor);
  SDL_SetTextureColorMod(this->texturaSDL_, color.r, color.g, color.b);
}

Texto::Texto(Texto &&other) {
  this->texturaSDL_ = other.texturaSDL_;
  this->font = other.font;
  other.texturaSDL_ = nullptr;
  other.font = nullptr;
}

Texto &Texto::operator=(Texto &&other) {
  if (this == &other) {
    return *this;
  }
  if (this->texturaSDL_) {
    SDL_DestroyTexture(texturaSDL_);
  }
  if (this->font) {
    TTF_CloseFont(this->font);
    TTF_Quit();
  }
  this->texturaSDL_ = other.texturaSDL_;
  this->font = other.font;

  other.texturaSDL_ = nullptr;
  other.font = nullptr;
  return *this;
}

Texto::~Texto() {
  if (texturaSDL_ != nullptr) {
    SDL_DestroyTexture(texturaSDL_);
  }
  if (font != nullptr) {
    TTF_CloseFont(this->font);
    TTF_Quit();
  }
}