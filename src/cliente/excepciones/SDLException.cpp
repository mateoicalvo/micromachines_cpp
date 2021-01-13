#include "includes/cliente/excepciones/SDLException.h"

SDLException::SDLException(const char* descripcion, const char* errorSDL) :
    std::exception(),
    descripcion_(descripcion) {
    
    descripcion_.append("\n |-ERROR_SDL: ").append(errorSDL);
}

const char* SDLException::what() const noexcept {
    return descripcion_.c_str();
}
