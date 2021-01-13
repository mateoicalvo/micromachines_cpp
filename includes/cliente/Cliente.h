#ifndef _CLIENTE_H_
#define _CLIENTE_H_

#include <string>
#include <SDL2/SDL.h>

#include "includes/common/RecibidorEventos.h"
#include "includes/common/EnviadorEventos.h"
#include "includes/common/eventos/Evento.h"

#include "includes/cliente/GUI/Ventana.h"
#include "includes/cliente/GUI/Renderizador.h"
#include "includes/cliente/GUI/eventos/EventoGUI.h"
#include "includes/cliente/GUI/HiloDibujador.h"
#include "includes/cliente/red/SocketTCPCliente.h"
#include "includes/cliente/grabador/HiloGrabador.h"

class Cliente {
 private:
  ColaProtegida<std::shared_ptr<EventoGUI>> eventosGUI_;
  bool seguirCorriendo;
  Ventana ventana_;
  Renderizador renderizador_;
  HiloGrabador grabador_;
  HiloDibujador dibujador_;
  SocketTCPCliente socket_;
  RecibidorEventos recibidor_;
  ColaBloqueante<std::shared_ptr<Evento>> eventosAEnviar_;
  EnviadorEventos enviador_;

  void manejarKeyUp(SDL_Event &eventoSDL);
  void manejarKeyDown(SDL_Event &eventoSDL);
  void manejarMouseDown(SDL_Event &eventoSDL);

 public:
  Cliente(unsigned int anchoVentana,
          unsigned int altoVentana,
          bool pantallaCompleta,
          const std::string &tituloVentana,
          const std::string &host,
          const std::string &puerto);
  void correr();
  void cerrar();
  ~Cliente();
};

#endif

