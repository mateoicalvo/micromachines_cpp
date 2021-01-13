#ifndef _VENTANA_H_
#define _VENTANA_H_

#include <string>

#include "includes/cliente/GUI/Area.h"

//Forward declarations:
class SDL_Window;

class Ventana {
private:
    SDL_Window* ventanaSDL_;
    unsigned int ancho_;
    unsigned int alto_;
    bool fullscreen_;

    Ventana(const Ventana&) = delete;
    Ventana& operator=(const Ventana&) = delete;

public:
    Ventana(unsigned int ancho, unsigned int alto, bool pantallaCompleta, const std::string& tituloVentana);
    ~Ventana();

    Area dimensiones();
    unsigned int ancho();
    unsigned int alto();
    void toggleFullScreen();


    SDL_Window* getSDL();

private:
    SDL_Window* crearConFullScreen(unsigned int ancho, unsigned int alto, const std::string& tituloPantalla);
    SDL_Window* crearSinFullScreen(unsigned int ancho, unsigned int alto, const std::string& tituloPantalla);
};

#endif
