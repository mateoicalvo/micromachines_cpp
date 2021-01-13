#include "includes/cliente/Cliente.h"

#include <iostream>
#include <includes/cliente/GUI/eventos/EventoGUIKeyUp.h>

#include "includes/cliente/GUI/eventos/EventoGUIClick.h"
#include "includes/cliente/GUI/eventos/EventoGUIKeyDown.h"

Cliente::Cliente(unsigned int anchoVentana,
                 unsigned int altoVentana,
                 bool pantallaCompleta,
                 const std::string &tituloVentana,
                 const std::string &host,
                 const std::string &puerto) :
    seguirCorriendo(false),
    ventana_(anchoVentana, altoVentana, pantallaCompleta, tituloVentana),
    renderizador_(ventana_),
    dibujador_(ventana_, renderizador_, grabador_, eventosGUI_, eventosAEnviar_,seguirCorriendo),
    socket_(host, puerto),
    recibidor_(socket_, dibujador_.eventosEntrantes(), 0),
    enviador_(socket_, eventosAEnviar_) {
}

Cliente::~Cliente() {
  dibujador_.join();
  enviador_.join();
  recibidor_.join();
  grabador_.join();
}

void Cliente::correr() {
    try {
      socket_.conectar();
    }
    catch (const std::exception &e) {
      std::cerr << e.what() << '\n';
    }
    this->seguirCorriendo = true;
    recibidor_.iniciar();
    enviador_.iniciar();
    dibujador_.iniciar();
    //TODO: Mover a inputhandler, que será de teclas o LUA
    SDL_Event evento;
    while (SDL_WaitEvent(&evento) && seguirCorriendo) {
      switch (evento.type) {
        case SDL_KEYDOWN:manejarKeyDown(evento);
          break;
        case SDL_KEYUP:manejarKeyUp(evento);
          break;
        case SDL_MOUSEBUTTONDOWN:manejarMouseDown(evento);
          break;
        case SDL_QUIT:seguirCorriendo = false;
          break;
        default:break;
      }
    }
}

void Cliente::cerrar() {
  dibujador_.detener();
  eventosAEnviar_.detener();
  enviador_.detener();
  recibidor_.detener();
  socket_.cerrarLectoEscritura();
  if (grabador_.estaCorriendo()){
    grabador_.detener();
  }
}

void Cliente::manejarKeyDown(SDL_Event &eventoSDL) {
  SDL_KeyboardEvent &keyEvent = (SDL_KeyboardEvent &) eventoSDL;
  if (eventoSDL.key.repeat != 0) {
    return;
  }
  std::shared_ptr<EventoGUI> evento;
  switch (keyEvent.keysym.sym) {
    case SDLK_c:evento = std::make_shared<EventoGUIKeyDown>(TECLA_C);
      eventosGUI_.put(evento);
      break;
    case SDLK_a:evento = std::make_shared<EventoGUIKeyDown>(TECLA_A);
      eventosGUI_.put(evento);
      break;
    case SDLK_z:evento = std::make_shared<EventoGUIKeyDown>(TECLA_Z);
      eventosGUI_.put(evento);
      break;
    case SDLK_LEFT:evento = std::make_shared<EventoGUIKeyDown>(TECLA_IZQ);
      eventosGUI_.put(evento);
      break;
    case SDLK_RIGHT:evento = std::make_shared<EventoGUIKeyDown>(TECLA_DER);
      eventosGUI_.put(evento);
      break;
    case SDLK_ESCAPE:evento = std::make_shared<EventoGUIKeyDown>(TECLA_ESC);
      eventosGUI_.put(evento);
      break;
    case SDLK_F11:evento = std::make_shared<EventoGUIKeyDown>(TECLA_FULLSCREEN);
      eventosGUI_.put(evento);
      break;
    case SDLK_g:
      if (grabador_.estaCorriendo()){
          grabador_.detener();
      } else {
          grabador_.join();
          grabador_.iniciar();
      }
      break;
    default:
      break;
  }
}

void Cliente::manejarKeyUp(SDL_Event &eventoSDL) {
  SDL_KeyboardEvent &keyEvent = (SDL_KeyboardEvent &) eventoSDL;
  if (eventoSDL.key.repeat != 0) {
    return;
  }
  std::shared_ptr<EventoGUI> evento;
  switch (keyEvent.keysym.sym) {
    case SDLK_a:evento = std::make_shared<EventoGUIKeyUp>(TECLA_A);
      eventosGUI_.put(evento);
      break;
    case SDLK_z:evento = std::make_shared<EventoGUIKeyUp>(TECLA_Z);
      eventosGUI_.put(evento);
      break;
    case SDLK_LEFT:evento = std::make_shared<EventoGUIKeyUp>(TECLA_IZQ);
      eventosGUI_.put(evento);
      break;
    case SDLK_RIGHT:evento = std::make_shared<EventoGUIKeyUp>(TECLA_DER);
      eventosGUI_.put(evento);
      break;
    default:break;
  }
}

void Cliente::manejarMouseDown(SDL_Event &eventoSDL) {
  if (eventoSDL.button.button != SDL_BUTTON_LEFT) {
    return;
  }
  int x, y;
  SDL_GetMouseState(&x, &y);
  std::shared_ptr<EventoGUI> eventoClick = std::make_shared<EventoGUIClick>(x, y);
  eventosGUI_.put(eventoClick);
}
