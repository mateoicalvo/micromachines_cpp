#include <iostream>
#include <includes/cliente/utils/ConfigCliente.h>
#include <includes/cliente/GUI/Texto.h>
#include "includes/cliente/GUI/escenas/EscenaPartida.h"
#include "includes/cliente/GUI/escenas/EscenaPodio.h"
#include "includes/cliente/GUI/Area.h"

// TODO: Refactorizar
void EscenaPartida::dibujarInterfaz(int iteracion) {
  Texto vida(CONFIG_CLIENTE.texto("salud"),
             CONFIG_CLIENTE.tamanioTexto("salud"),
             renderizador_,
             UUID_TEXTO_BLANCO);
  Animacion salud
      (AnimacionFactory::instanciar(UUID_ANIMACION_SALUD, this->renderizador_));
  Area areaVida =
      Area(CONFIG_CLIENTE.margenX("salud") * CONFIG_CLIENTE.anchoVentana(),
           CONFIG_CLIENTE.margenY("salud") * CONFIG_CLIENTE.altoVentana(),
           CONFIG_CLIENTE.anchoTexto("salud"),
           salud.alto());
  renderizador_.dibujarTexto(vida, areaVida);
  std::shared_ptr<ObjetoDinamico> principalCar = pista.obtenerObjeto(id_car);
  Area areaSalud = Area(CONFIG_CLIENTE.anchoTexto("salud") + 20,
                        CONFIG_CLIENTE.margenY("salud")
                            * CONFIG_CLIENTE.altoVentana(),
                        round(principalCar.get()->getVida() * salud.ancho()
                                  / 100),
                        salud.alto());
  renderizador_.dibujar(salud.get(iteracion), areaSalud);
}

void EscenaPartida::dibujarBarro(int iteracion) {
  Area areaBarro = Area(0,
                        0,
                        CONFIG_CLIENTE.anchoVentana()
                            * CONFIG_CLIENTE.factorLejaniaCamara(),
                        CONFIG_CLIENTE.altoVentana()
                            * CONFIG_CLIENTE.factorLejaniaCamara());
  renderizador_.dibujar(barro.getAnimacion().get(iteracion), areaBarro);
}

//TODO: Cargar la pista json una sola vez. Para la computadora y para la Pista
EscenaPartida::EscenaPartida(Renderizador &renderizador,
                             ColaProtegida<std::shared_ptr<EventoGUI>> &eventosGUI,
                             std::stack<std::shared_ptr<Escena>> &escenas,
                             ColaBloqueante<std::shared_ptr<Evento>> &eventosAEnviar_,
                             EventoPartidaIniciada &estadoInicial,
                             Sonido &musicaAmbiente,
                             bool juegaComputadora) :
    Escena(escenas, renderizador, eventosAEnviar_, musicaAmbiente),
    eventosGUI_(eventosGUI),
    pista("assets/pistas/1.json", renderizador),
    conversor(CONFIG_CLIENTE.pixelPorMetro(), CONFIG_CLIENTE.pixelPorBloque()),
    camara(conversor, pista, renderizador),
    barro(UUID_ANIMACION_BARRO_GRANDE,
          renderizador,
          CONFIG_CLIENTE.musicaVacio(),
          true) {
  this->musicaAmbiente.stop();
  const std::map<uint8_t, datosVehiculo_>
      &idsADatosVehiculos = estadoInicial.estadoInicial_.idsADatosVehiculos_;
  //FIXME: Esto no esta bueno
  int vehiculoActual = 800;
  for (const auto &kv : idsADatosVehiculos) {
    uint8_t id = kv.first;
    std::shared_ptr<ObjetoDinamico> vehiculo =
        std::make_shared<ObjetoDinamico>(vehiculoActual,
                                         renderizador,
                                         CONFIG_CLIENTE.musicaMotor(),
                                         true);
    pista.agregarObjeto(id, vehiculo);
    //FIXME: ESTO TAMBIEN ESTA FEO, LA PISTA DEBERIA DEJAR AGREGAR EN X; Y; ANGULO; TAMBIEN CON VIDA?
    int xCoord = conversor.metroAPixel(kv.second.xCoord_);
    int yCoord = conversor.metroAPixel(kv.second.yCoord_);
    uint16_t angulo = kv.second.angulo_;

    pista.obtenerObjeto(id)->mover(xCoord, yCoord, angulo);
    vehiculoActual += 10;

    if (juegaComputadora) {
      jugador_ = std::make_shared<Computadora>(eventosAEnviar_, "assets/pistas/1.json");
    } else {
      jugador_ =std::make_shared<Jugador>(eventosAEnviar_);
    }
  }
  camara.setCar(pista.obtenerObjeto(estadoInicial.idDelVehiculo_));
  this->id_car = estadoInicial.idDelVehiculo_;
  jugador_->empezar();
  this->barroActivo = false;
}

Textura EscenaPartida::dibujate(uint32_t numeroIteracion, Area dimensiones) {
  float reescalado = CONFIG_CLIENTE.factorLejaniaCamara();
  Area nueva = Area(0,
                    0,
                    dimensiones.ancho() * reescalado,
                    dimensiones.alto() * reescalado);
  Textura miTextura(renderizador_, nueva);
  renderizador_.setDestino(miTextura);
  this->camara.setWidthHeight(nueva.ancho(), nueva.alto());
  camara.dibujarPista(numeroIteracion);
  std::shared_ptr<ObjetoDinamico> principalCar = pista.obtenerObjeto(id_car);
  Animacion &animacion = principalCar.get()->getAnimacion();
  Area areaFondo =
      Area(nueva.ancho() / 2 - (float) animacion.ancho() / 2.0f,
           nueva.alto() / 2 - (float) animacion.alto() / 2.0f,
           animacion.ancho(),
           animacion.alto());
  renderizador_.dibujar(animacion.get(numeroIteracion),
                        areaFondo,
                        principalCar.get()->getAngulo(),
                        false);
  camara.dibujarObjetos(id_car, numeroIteracion);
  camara.dibujarEventosTemporales(numeroIteracion);
  if (barroActivo)
    dibujarBarro(numeroIteracion);
  dibujarInterfaz(numeroIteracion);
  return miTextura;
}

void EscenaPartida::manejarInput(EventoGUI &evento) {
  evento.actualizar((EventoGUIHandler &) (*this));
}

void EscenaPartida::manejarInput(EventoGUIClick &evento) {}

void EscenaPartida::manejarInput(EventoGUIKeyDown &evento) {
  if (evento.getTecla() == TECLA_FULLSCREEN) {
    renderizador_.toggleFullScreen();
  } else if (evento.getTecla() == TECLA_ESC) {
    escenas_.pop();
  } else if (evento.getTecla() == TECLA_A) {
    jugador_->acelerar();
  } else if (evento.getTecla() == TECLA_Z) {
    jugador_->frenar();
  } else if (evento.getTecla() == TECLA_IZQ) {
    jugador_->doblarIzquierda();
  } else if (evento.getTecla() == TECLA_DER) {
    jugador_->doblarDerecha();
  }
}

void EscenaPartida::manejarInput(EventoGUIKeyUp &evento) {
  if (evento.getTecla() == TECLA_A) {
    jugador_->desacelerar();
  } else if (evento.getTecla() == TECLA_Z) {
    jugador_->dejarDeFrenar();
  } else if (evento.getTecla() == TECLA_IZQ) {
    jugador_->dejarDeDoblarIzquierda();
  } else if (evento.getTecla() == TECLA_DER) {
    jugador_->dejarDeDoblarDerecha();
  }
}

void EscenaPartida::manejar(Evento &e) {
  e.actualizar((Handler &) (*this));
}

void EscenaPartida::manejar(EventoSnapshot &e) {
  std::map<uint8_t, datosVehiculo_> datos = e.idsADatosVehiculos_;
  for (const auto &kv : datos) {
    float posX = this->conversor.metroAPixel(kv.second.xCoord_);
    float posY = this->conversor.bloqueAPixel(pista.getSizeY())
        - this->conversor.metroAPixel(kv.second.yCoord_);
    this->pista.obtenerObjeto(kv.first).get()->mover(posX,
                                                     posY,
                                                     kv.second.angulo_);
    this->pista.obtenerObjeto(kv.first).get()->setVida(kv.second.salud_);
  }
  jugador_->setEstado(datos[this->id_car].xCoord_,
                      datos[this->id_car].yCoord_,
                      datos[this->id_car].angulo_);
}

void EscenaPartida::manejar(EventoChoque &e) {
  float posX = this->conversor.metroAPixel(e.xCoord_);
  float posY = this->conversor.bloqueAPixel(pista.getSizeY())
      - this->conversor.metroAPixel(e.yCoord_);
  std::shared_ptr<ObjetoDinamico> choque =
      std::make_shared<ObjetoDinamico>(UUID_ANIMACION_VACIA,
                                       renderizador_,
                                       CONFIG_CLIENTE.musicaChoque(),
                                       false);
  choque.get()->mover(posX, posY, 0);
  pista.agregarEventoTemporal(choque);
}

void EscenaPartida::manejar(EventoFrenada &e) {
  float posX = this->conversor.metroAPixel(e.xCoord_);
  float posY = this->conversor.bloqueAPixel(pista.getSizeY())
      - this->conversor.metroAPixel(e.yCoord_);
  std::shared_ptr<ObjetoDinamico> frenada =
      std::make_shared<ObjetoDinamico>(UUID_ANIMACION_VACIA,
                                       renderizador_,
                                       CONFIG_CLIENTE.musicaFrenada(),
                                       false);
  frenada.get()->mover(posX, posY, 0);
  pista.agregarEventoTemporal(frenada);
}

void EscenaPartida::manejar(EventoExplosion &e) {
  float posX = this->conversor.metroAPixel(e.xCoord_);
  float posY = this->conversor.bloqueAPixel(pista.getSizeY())
      - this->conversor.metroAPixel(e.yCoord_);
  std::shared_ptr<ObjetoDinamico> explosion =
      std::make_shared<ObjetoDinamico>(UUID_ANIMACION_EXPLOSION,
                                       renderizador_,
                                       CONFIG_CLIENTE.musicaExplosion(),
                                       false);
  explosion.get()->mover(posX, posY, 0);
  pista.agregarEventoTemporal(explosion);
}

void EscenaPartida::manejar(EventoBarroPisado &e) {
  this->barroActivo = true;
}

void EscenaPartida::manejar(EventoFinBarro &e) {
  this->barroActivo = false;
}

void EscenaPartida::manejar(EventoFinCarrera &e) {
  std::map<int, std::shared_ptr<ObjetoDinamico>> mapaAutos;
  for (uint8_t i = 0; i < e.podio_.size(); i++) {
    mapaAutos.insert(std::pair<int, std::shared_ptr<ObjetoDinamico>>(i,
                                                                     pista.obtenerObjeto(
                                                                         e.podio_[i])));
  }
  escenas_.emplace(std::make_shared<EscenaPodio>(renderizador_,
                                                 eventosGUI_,
                                                 escenas_,
                                                 eventosAEnviar_,
                                                 this->musicaAmbiente,
                                                 mapaAutos));
}

void EscenaPartida::manejar(EventoAparecioConsumible& e) {
  int idAnimacion = 0;
  if (e.tipoConsumible_ == UUID_VIDA) {
    idAnimacion = UUID_ANIMACION_CAJAS_SALUD;
  } else if (e.tipoConsumible_ == UUID_BOOST) {
    idAnimacion = UUID_ANIMACION_BOOST;
  } else if (e.tipoConsumible_ == UUID_BARRO) {
    idAnimacion = UUID_ANIMACION_BARRO;
  } else if (e.tipoConsumible_ == UUID_PIEDRA) {
    idAnimacion = UUID_ANIMACION_PIEDRA;
  } else if (e.tipoConsumible_ == UUID_ACEITE) {
    idAnimacion = UUID_ANIMACION_ACEITE;
  } 

  std::shared_ptr<ObjetoDinamico> consumible =
        std::make_shared<ObjetoDinamico>(idAnimacion,
                                         this->renderizador_,
                                         CONFIG_CLIENTE.musicaVacio(),
                                         false);
    

    float posX = this->conversor.metroAPixel(e.xCoord_);
    float posY = this->conversor.bloqueAPixel(pista.getSizeY())
        - this->conversor.metroAPixel(e.yCoord_);
    
    consumible->mover(posX, posY, 0);

    pista.agregarObjeto(e.uuidConsumible_, consumible);  
}

void EscenaPartida::manejar(EventoDesaparecioConsumible& e) {
  pista.borrarObjeto(e.uuidConsumible_);
}

EscenaPartida::~EscenaPartida() {
  jugador_->terminar();
}
