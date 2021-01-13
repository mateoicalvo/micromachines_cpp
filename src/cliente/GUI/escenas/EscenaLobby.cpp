#include "includes/cliente/GUI/escenas/EscenaLobby.h"

#include "includes/cliente/GUI/escenas/EscenaPartida.h"
#include "includes/cliente/GUI/AnimacionFactory.h"
#include "includes/cliente/utils/ConfigCliente.h"
#include "includes/cliente/GUI/Area.h"

void EscenaLobby::inicializarBotones() {
  int anchoVentana = CONFIG_CLIENTE.anchoVentana();
  int altoVentana = CONFIG_CLIENTE.altoVentana();

  this->botones.emplace(UUID_BOTON_INICIAR_PARTIDA,
                        std::make_shared<Boton>(UUID_BOTON_INICIAR_PARTIDA,
                                                renderizador_,
                                                0.10 * anchoVentana,
                                                0.60 * altoVentana));

  this->botones.emplace(UUID_BOTON_ATRAS,
                        std::make_shared<Boton>(UUID_BOTON_ATRAS,
                                                renderizador_,
                                                0.10 * anchoVentana,
                                                0.70 * altoVentana));
  this->botones.emplace(UUID_BOTON_CIRCULAR,
                        std::make_shared<Boton>(UUID_BOTON_CIRCULAR,
                                                renderizador_,
                                                0.40 * anchoVentana,
                                                0.80 * altoVentana));
}

void EscenaLobby::inicializarTextoJugadores() {
  int tamanioFuente = 30;
  textoJugadores.clear();
  for (size_t i = 0; i < jugadoresId.size(); ++i) {
    std::string texto = "Jugador " + std::to_string(jugadoresId.at(i));
    int color = UUID_TEXTO_AMARILLO;
    if (jugadoresEstaListo.at(i)) {
      std::cout << "Es true\n";
      color = UUID_TEXTO_VERDE;
    }
    textoJugadores.emplace(i, std::make_shared<Texto>(texto,
                                                      tamanioFuente,
                                                      renderizador_,
                                                      color));
  }
  int color = UUID_TEXTO_BLANCO;
  if (cpu) {
    color = UUID_TEXTO_VERDE;
  }
  textoJugadores.emplace(99, std::make_shared<Texto>("CPU",
                                                     tamanioFuente,
                                                     renderizador_,
                                                     color));
}

void EscenaLobby::dibujarBotones(int nroIteracion) {
  for (const auto &boton: botones) {
    Animacion &animacion = boton.second.get()->getAnimacion();
    Area areaBoton = Area(boton.second.get()->getX(),
                          boton.second.get()->getY(),
                          animacion.ancho(),
                          animacion.alto());
    renderizador_.dibujar(animacion.get(nroIteracion), areaBoton);
  }
}

void EscenaLobby::handlerBotones(int uuid) {
  switch (uuid) {
    case UUID_BOTON_INICIAR_PARTIDA: {
      std::shared_ptr<Evento> jugar = std::make_shared<EventoIniciarPartida>();
      eventosAEnviar_.put(jugar);
      break;
    }
    case UUID_BOTON_ATRAS: {
      escenas_.pop();
    }
    case UUID_BOTON_CIRCULAR: {
      cpu = !cpu;
      inicializarTextoJugadores();
    }
    default:break;
  }
}

void EscenaLobby::dibujarTextoJugadores(int iteracion) {
  double i = 0;
  int anchoVentana = CONFIG_CLIENTE.anchoVentana();
  int altoVentana = CONFIG_CLIENTE.altoVentana();
  for (const auto &textoJugador: textoJugadores) {
    if (textoJugador.first != 99) {
      Area areaTexto = Area(0.45 * anchoVentana,
                            (0.42 + i) * altoVentana,
                            247,
                            31);
      renderizador_.dibujarTexto(*(textoJugador.second.get()), areaTexto);
      i = i + 0.10;
    } else {
      Area areaTextoCPU = Area(0.41 * anchoVentana,
                               0.80 * altoVentana,
                               50,
                               50);
      renderizador_.dibujarTexto(*(textoJugadores.at(99)), areaTextoCPU);
    }
  }

}

EscenaLobby::EscenaLobby(Renderizador &renderizador,
                         ColaProtegida<std::shared_ptr<EventoGUI>> &eventosGUI,
                         std::stack<std::shared_ptr<Escena>> &escenas,
                         ColaBloqueante<std::shared_ptr<Evento>> &eventosAEnviar_,
                         Sonido &musicaAmbiente,
                         EventoPartidaCreada &e) :
    Escena(escenas, renderizador, eventosAEnviar_, musicaAmbiente),
    fondoMenu_(AnimacionFactory::instanciar(CONFIG_CLIENTE.uuid("fondoSala"),
                                            renderizador)),
    eventosGUI_(eventosGUI),
    cpu(false) {

  jugadoresId.emplace(0, e.uuidCreador_);
  jugadoresEstaListo.emplace(0, false);
  inicializarBotones();
  inicializarTextoJugadores();
}

EscenaLobby::EscenaLobby(Renderizador &renderizador,
                         ColaProtegida<std::shared_ptr<EventoGUI>> &eventosGUI,
                         std::stack<std::shared_ptr<Escena>> &escenas,
                         ColaBloqueante<std::shared_ptr<Evento>> &eventosAEnviar_,
                         Sonido &musicaAmbiente,
                         EventoSnapshotLobby &e) :
    Escena(escenas, renderizador, eventosAEnviar_, musicaAmbiente),
    fondoMenu_(AnimacionFactory::instanciar(CONFIG_CLIENTE.uuid("fondoSala"),
                                            renderizador)),
    eventosGUI_(eventosGUI) {

  int ordinal = 0;
  for (const auto &kv : e.idJugadorAEstaListo_) {
    jugadoresId.emplace(ordinal, kv.first);
    jugadoresEstaListo.emplace(ordinal, kv.second);
    ordinal++;
  }
  inicializarBotones();
  inicializarTextoJugadores();
}

Textura EscenaLobby::dibujate(uint32_t numeroIteracion, Area dimensiones) {
  Textura miTextura(renderizador_, dimensiones);
  renderizador_.setDestino(miTextura);
  Area areaFondo = Area(0, 0, dimensiones.ancho(), dimensiones.alto());
  renderizador_.dibujar(fondoMenu_.get(numeroIteracion), areaFondo);
  dibujarBotones(numeroIteracion);
  dibujarTextoJugadores(numeroIteracion);
  return miTextura;
}

void EscenaLobby::manejarInput(EventoGUI &evento) {
  evento.actualizar(*this);
}

void EscenaLobby::manejarInput(EventoGUIClick &evento) {
  int x, y;
  SDL_GetMouseState(&x, &y);
  for (const auto &boton: botones) {
    if (boton.second.get()->estaSeleccionado(x, y)) {
      handlerBotones(boton.first);
      break;
    }
  }
}

void EscenaLobby::manejarInput(EventoGUIKeyDown &evento) {
  if (evento.getTecla() == TECLA_ESC) {
    escenas_.pop();
  }
  if (evento.getTecla() == TECLA_FULLSCREEN) {
    renderizador_.toggleFullScreen();
  }
}

void EscenaLobby::manejarInput(EventoGUIKeyUp &evento) {}

void EscenaLobby::manejar(Evento &e) {
  e.actualizar(*this);
}

void EscenaLobby::manejar(EventoPartidaIniciada &estadoInicial) {
  escenas_.emplace(std::make_shared<EscenaPartida>(renderizador_,
                                                   eventosGUI_,
                                                   escenas_,
                                                   eventosAEnviar_,
                                                   estadoInicial,
                                                   this->musicaAmbiente,
                                                   cpu));
}

void EscenaLobby::manejar(EventoSnapshotLobby &e) {
  jugadoresId.clear();
  jugadoresEstaListo.clear();
  int ordinal = 0;
  for (auto &kv : e.idJugadorAEstaListo_) {
    jugadoresId.emplace(ordinal, kv.first);
    jugadoresEstaListo.emplace(ordinal, kv.second);
    ordinal++;
  }
  inicializarTextoJugadores();
}
