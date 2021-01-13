#include "includes/cliente/GUI/escenas/EscenaSala.h"

#include "includes/cliente/GUI/escenas/EscenaLobby.h"
#include "includes/cliente/GUI/AnimacionFactory.h"
#include "includes/cliente/utils/ConfigCliente.h"
#include "includes/cliente/GUI/Area.h"
#include "includes/cliente/GUI/Texto.h"

void EscenaSala::inicializarBotones() {
  botones.clear();
  int anchoVentana = CONFIG_CLIENTE.anchoVentana();
  int altoVentana = CONFIG_CLIENTE.altoVentana();
  botones.clear();
  this->botones.emplace(UUID_BOTON_CREAR_PARTIDA,
    std::make_shared<Boton>(UUID_BOTON_CREAR_PARTIDA,
                              renderizador_,
                              0.10 * anchoVentana,
                              0.60 * altoVentana));

  this->botones.emplace(UUID_BOTON_UNIRSE_A_PARTIDA,
    std::make_shared<Boton>(UUID_BOTON_UNIRSE_A_PARTIDA,
                              renderizador_,
                              0.10 * anchoVentana,
                              0.65 * altoVentana));

  this->botones.emplace(UUID_BOTON_ATRAS,
    std::make_shared<Boton>(UUID_BOTON_ATRAS,
                              renderizador_,
                              0.10 * anchoVentana,
                              0.70 * altoVentana));

  // BOTONES VACIOS PARA LAS PARTIDAS
  float posicionRelativaX = 0.45f;
  float posicionRelativaY = 0.42f;

  int restanDibujar = partidasId.size() > 4 ? 4 : partidasId.size();

  for (size_t i = 0; i < partidasId.size(); ++i) {
    if (restanDibujar == 0) {
      break;
    }
    this->botones.emplace(i, std::make_shared<Boton>(UUID_BOTON_VACIO,
      renderizador_,
      posicionRelativaX * anchoVentana,
      posicionRelativaY * altoVentana
      ));
    posicionRelativaY += 0.10f;
    restanDibujar--;
  }

  this->botones.emplace(4, std::make_shared<Boton>(UUID_BOTON_UP,
                              renderizador_,
                              0.80 * anchoVentana,
                              0.42 * altoVentana));

  this->botones.emplace(5, std::make_shared<Boton>(UUID_BOTON_DOWN,
                              renderizador_,
                              0.80 * anchoVentana,
                              0.72 * altoVentana));
}

void EscenaSala::inicializarTextoPartidas() {
  textoPartidas.clear();
  if (finVentana_ > partidasId.size()) {
    inicioVentana_ = 0;
    finVentana_ = 4;
  }
  int tamanioFuente = 30;
  int restanDibujar = partidasId.size() > 4 ? 4 : partidasId.size();
  uint16_t skips = inicioVentana_;
  int dibujadas = 0;
  for (auto i = partidasId.begin(); i != partidasId.end(); i++) {
    if (skips > 0) {
      skips--;
      continue;
    }
    if (restanDibujar == 0) {
      break;
    }
    std::string texto = "Partida " + std::to_string(i->second);
    textoPartidas.emplace(dibujadas, std::make_shared<Texto>(texto,
      tamanioFuente,
      renderizador_,
      UUID_TEXTO_BLANCO));
    restanDibujar--;
    dibujadas++;
  }
}

void EscenaSala::dibujarBotones(int nroIteracion) {
  for (const auto &boton: botones) {
    Animacion &animacion = boton.second.get()->getAnimacion();
    Area areaBoton = Area(boton.second.get()->getX(),
                          boton.second.get()->getY(),
                          animacion.ancho(),
                          animacion.alto());
    renderizador_.dibujar(animacion.get(nroIteracion), areaBoton);
  }
}

void EscenaSala::dibujarTextoPartidas(int iteracion) {
  for (const auto &textoPartida: textoPartidas) {
    std::shared_ptr<Boton> botonAsociado = botones.at(textoPartida.first);
    Animacion &animacion = botonAsociado.get()->getAnimacion();
    Area areaTexto = Area(botonAsociado.get()->getX(),
                          botonAsociado.get()->getY(),
                          animacion.ancho(),
                          animacion.alto());
    renderizador_.dibujarTexto(*(textoPartida.second.get()), areaTexto);
  }
}

void EscenaSala::handlerBotones(int uuid) {
  switch (uuid) {
    case UUID_BOTON_CREAR_PARTIDA: {
      std::shared_ptr<Evento> crearPartida = std::make_shared<EventoCrearPartida>();
      eventosAEnviar_.put(crearPartida);
      break;
    }
    case UUID_BOTON_UNIRSE_A_PARTIDA: {
      if (partidaSeleccionada != -1) {
        std::shared_ptr<Evento>
            eventoUnirseAPartida =
            std::make_shared<EventoUnirseAPartida>(partidasId.at(
                partidaSeleccionada));
        eventosAEnviar_.put(eventoUnirseAPartida);
      }
      break;
    }
    case 0: {
      if (!partidasId.empty()) {
        partidaSeleccionada = 0;
        for (const auto &texto:textoPartidas){
          texto.second.get()->setColor(UUID_TEXTO_BLANCO);
        }
        textoPartidas.at(0).get()->setColor(UUID_TEXTO_AMARILLO);
        break;
      }
    }
    case 1: {
      if (!partidasId.empty()) {
        partidaSeleccionada = 1;
        for (const auto &texto:textoPartidas){
          texto.second.get()->setColor(UUID_TEXTO_BLANCO);
        }
        textoPartidas.at(1).get()->setColor(UUID_TEXTO_AMARILLO);
        break;
      }
    }
    case 2: {
      if (!partidasId.empty()) {
        partidaSeleccionada = 2;
        for (const auto &texto:textoPartidas){
          texto.second.get()->setColor(UUID_TEXTO_BLANCO);
        }
        textoPartidas.at(2).get()->setColor(UUID_TEXTO_AMARILLO);
        break;
      }
    }
    case 3: {
      if (!partidasId.empty()) {
        partidaSeleccionada = 3;
        for (const auto &texto:textoPartidas){
          texto.second.get()->setColor(UUID_TEXTO_BLANCO);
        }
        textoPartidas.at(3).get()->setColor(UUID_TEXTO_AMARILLO);
        break;
      }
    }
    case UUID_BOTON_ATRAS: {
      escenas_.pop();
    }
    //TOCO BOTON UP
    case 4:
      if (inicioVentana_ <= 0) {
        return;
      }
      inicioVentana_--;
      finVentana_--;
      inicializarBotones();
      inicializarTextoPartidas();
      break;
    //TOCO BOTON DOWN
    case 5:
      if (finVentana_ == 0xFFFF || finVentana_ == partidasId.size()) {
        return;
      }
      inicioVentana_++;
      finVentana_++;
      inicializarBotones();
      inicializarTextoPartidas();
      break;
    default:break;
  }
  partidaSeleccionada += inicioVentana_;
}

EscenaSala::EscenaSala(Renderizador &renderizador,
                       ColaProtegida<std::shared_ptr<EventoGUI>> &eventosGUI,
                       std::stack<std::shared_ptr<Escena>> &escenas,
                       ColaBloqueante<std::shared_ptr<Evento>> &eventosAEnviar_,
                       Sonido &musicaAmbiente,
                       EventoSnapshotSala& e) :
    Escena(escenas, renderizador, eventosAEnviar_, musicaAmbiente),
    fondoMenu_(AnimacionFactory::instanciar(CONFIG_CLIENTE.uuid("fondoSala"),
                                            renderizador)),
    eventosGUI_(eventosGUI),
    inicioVentana_(0),
    finVentana_(4) {
  
  for (const auto& kv : e.ordinalAuuidPartida_) {
    partidasId.emplace(kv.first, kv.second);
  }
  partidaSeleccionada = -1;
  inicializarBotones();
  inicializarTextoPartidas();
}

Textura EscenaSala::dibujate(uint32_t numeroIteracion, Area dimensiones) {
  Textura miTextura(renderizador_, dimensiones);
  renderizador_.setDestino(miTextura);
  Area areaFondo = Area(0, 0, dimensiones.ancho(), dimensiones.alto());
  renderizador_.dibujar(fondoMenu_.get(numeroIteracion), areaFondo);
  dibujarBotones(numeroIteracion);
  dibujarTextoPartidas(numeroIteracion);
  return miTextura;
}

void EscenaSala::manejarInput(EventoGUI &evento) {
  evento.actualizar(*this);
}

void EscenaSala::manejarInput(EventoGUIClick &evento) {
  int x, y;
  SDL_GetMouseState(&x, &y);
  for (const auto &boton: botones) {
    if (boton.second.get()->estaSeleccionado(x, y)) {
      handlerBotones(boton.first);
      break;
    }
  }
}

void EscenaSala::manejarInput(EventoGUIKeyDown &evento) {
  if (evento.getTecla() == TECLA_ESC) {
    escenas_.pop();
  }
  if (evento.getTecla() == TECLA_FULLSCREEN) {
    renderizador_.toggleFullScreen();
  }
}

void EscenaSala::manejarInput(EventoGUIKeyUp &evento) {}

void EscenaSala::manejar(Evento &e) {
  e.actualizar(*this);
}

void EscenaSala::manejar(EventoSnapshotSala& e) {
  partidasId.clear();
  for (const auto& kv : e.ordinalAuuidPartida_) {
    partidasId.emplace(kv.first, kv.second);
  }
  inicioVentana_ = 0;
  finVentana_ = 4;
  inicializarBotones();
  inicializarTextoPartidas();
}

void EscenaSala::manejar(EventoPartidaCreada& e) {
  //TODO: EL uuid partida puede servir para mostrar por texto cual es
  std::shared_ptr<Evento> unirme = std::make_shared<EventoUnirseAPartida>(e.uuidPartida_);
  eventosAEnviar_.put(unirme);
  escenas_.emplace(std::make_shared<EscenaLobby>(renderizador_,
                                                     eventosGUI_,
                                                     escenas_,
                                                     eventosAEnviar_,
                                                     this->musicaAmbiente,
                                                     e));
}

void EscenaSala::manejar(EventoSnapshotLobby& e) {
  escenas_.emplace(std::make_shared<EscenaLobby>(renderizador_,
                                                       eventosGUI_,
                                                       escenas_,
                                                       eventosAEnviar_,
                                                       this->musicaAmbiente,
                                                       e));
}
