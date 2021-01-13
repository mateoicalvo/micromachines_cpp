#include "includes/cliente/GUI/Ventana.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

#include "includes/cliente/excepciones/SDLException.h"

Ventana::Ventana(unsigned int ancho, unsigned int alto, bool pantallaCompleta, const std::string& tituloVentana) :
    ancho_(ancho),
    alto_(alto),
    fullscreen_(false) {
    
    int errCode = SDL_Init(SDL_INIT_VIDEO);
    if (errCode) {
        throw SDLException("Error en la inicialización", SDL_GetError());
    }
    if (pantallaCompleta) {
        ventanaSDL_ = crearConFullScreen(ancho, alto, tituloVentana);
    } else {
        ventanaSDL_ = crearSinFullScreen(ancho, alto, tituloVentana);
    }
}

Ventana::~Ventana() {
    SDL_DestroyWindow(ventanaSDL_);
    SDL_Quit();
}

//TODO: No tiene mucho sentido el 0, 0
Area Ventana::dimensiones() {
    return Area(0, 0, ancho_, alto_);
}

unsigned int Ventana::ancho() {
    return ancho_;
}

unsigned int Ventana::alto() {
    return alto_;
}

void Ventana::toggleFullScreen() {
    if (!fullscreen_) {
        SDL_SetWindowFullscreen(ventanaSDL_, SDL_WINDOW_FULLSCREEN);    
    } else {
        SDL_SetWindowFullscreen(ventanaSDL_, 0);    
    }
    fullscreen_ = !fullscreen_;
}

SDL_Window* Ventana::getSDL() {
    return ventanaSDL_;
}

SDL_Window* Ventana::crearSinFullScreen(unsigned int ancho, unsigned int alto, const std::string& tituloVentana) {
    ventanaSDL_ = SDL_CreateWindow(
        tituloVentana.c_str(),                  
        SDL_WINDOWPOS_UNDEFINED,           
        SDL_WINDOWPOS_UNDEFINED,           
        ancho,                              
        alto,                              
        SDL_WINDOW_OPENGL                 
    );
    if (!ventanaSDL_) {
        throw SDLException("Error en la creación de la ventana", SDL_GetError());
    }
    return ventanaSDL_;
}

SDL_Window* Ventana::crearConFullScreen(unsigned int ancho, unsigned int alto, const std::string& tituloVentana) {
    ventanaSDL_ = SDL_CreateWindow(
        tituloVentana.c_str(),                 
        SDL_WINDOWPOS_UNDEFINED,        
        SDL_WINDOWPOS_UNDEFINED,          
        ancho,                              
        alto,                               
        SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN
    );
    if (!ventanaSDL_) {
        throw SDLException("Error en la creación de la ventana", SDL_GetError());
    }
    return ventanaSDL_;
}
