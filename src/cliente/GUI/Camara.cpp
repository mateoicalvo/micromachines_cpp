#include "includes/cliente/GUI/Camara.h"

Camara::Camara(Conversor &conversor, Pista &pista, Renderizador &renderizador) :
    conversor(conversor), pista(pista), renderizador_(renderizador) {
  xInicial = 0;
  xFinal = 0;
  yInicial = 0;
  yFinal = 0;
}

void Camara::setWidthHeight(int width, int height) {
  this->width = width;
  this->height = height;
}
void Camara::setCar(std::shared_ptr<ObjetoDinamico> car) {
  this->car = car;
  car.get()->getSonido().setVolume(30);
}

void Camara::dibujarPista(int iteracion) {
  int posCarX = conversor.pixelABloque(car.get()->getX());
  int posCarY = conversor.pixelABloque(car.get()->getY());
  xInicial = posCarX - (conversor.pixelABloque(width / 2) + 1);
  xFinal = posCarX + (conversor.pixelABloque(width / 2) + 2);
  yInicial = posCarY - (conversor.pixelABloque(height / 2) + 1);
  yFinal = posCarY + (conversor.pixelABloque(height / 2) + 2);
  if (xInicial < 0) {
    xInicial = 0;
  }
  if (yInicial < 0) {
    yInicial = 0;
  }
  if (xFinal > pista.getSizeX()) {
    xFinal = pista.getSizeX();
  }
  if (yFinal > pista.getSizeY()) {
    yFinal = pista.getSizeY();
  }

  int nroCapas = pista.getCapas();
  for (int k = 0; k < nroCapas; k++) {
    for (int i = xInicial; i < xFinal; i++) {
      for (int j = yInicial; j < yFinal; j++) {
        std::shared_ptr<Animacion> animacion = pista.getBloque(k, i, j);
        if (animacion != nullptr) {
          Area areaFondo = Area(
              i * animacion.get()->ancho() - (car.get()->getX() - width / 2),
              j * animacion.get()->alto() - (car.get()->getY() - height / 2),
              animacion.get()->ancho(),
              animacion.get()->alto());
          renderizador_.dibujar(animacion.get()->get(iteracion), areaFondo);
        }
      }
    }
  }
}

void Camara::dibujarObjetos(int car_id, int iteracion) {
  int cantidadObjetos = 0;
  std::vector<int> idObjetos;
  pista.obtenerIds(idObjetos);
  for (uint16_t i = 0; i < idObjetos.size(); i++) {
    if (idObjetos[i] != car_id) {
      std::shared_ptr<ObjetoDinamico>
          objeto = pista.obtenerObjeto(idObjetos[i]);
      objeto.get()->getSonido().setVolume(0);
      if (objeto != nullptr) {
        int bloqueCarX = conversor.pixelABloque(objeto.get()->getX());
        int bloqueCarY = conversor.pixelABloque(objeto.get()->getY());
        if (bloqueCarX >= xInicial &&
            bloqueCarX <= xFinal &&
            bloqueCarY >= yInicial &&
            bloqueCarY <= yFinal) {
          if (cantidadObjetos <= 3) {
            objeto.get()->getSonido().setVolume(20);
            cantidadObjetos++;
          }
          Animacion &animacion = objeto.get()->getAnimacion();
          Area areaFondo = Area(
              objeto.get()->getX() - (this->car.get()->getX() - width / 2)
                  - (float) objeto->getAnimacion().ancho() / 2.0f,
              objeto.get()->getY() - (this->car.get()->getY() - height / 2)
                  - (float) objeto->getAnimacion().alto() / 2.0f,
              animacion.ancho(),
              animacion.alto());
          renderizador_.dibujar(animacion.get(iteracion),
                                areaFondo,
                                objeto.get()->getAngulo(),
                                false);
        }
      }
    }
  }
}

void Camara::dibujarEventosTemporales(int iteracion) {
  int cantidadEventos = 0;
  std::vector<int> idEventos;
  pista.obtenerIdsEventosTemporales(idEventos);
  for (uint16_t i = 0; i < idEventos.size(); i++) {
    std::shared_ptr<ObjetoDinamico>
        objeto = pista.obtenerEventoTemporal(idEventos[i]);
    objeto.get()->getSonido().setVolume(0);
    if (objeto != nullptr) {
      int bloqueCarX = conversor.pixelABloque(objeto.get()->getX());
      int bloqueCarY = conversor.pixelABloque(objeto.get()->getY());
      if (bloqueCarX >= xInicial &&
          bloqueCarX <= xFinal &&
          bloqueCarY >= yInicial &&
          bloqueCarY <= yFinal) {
        if (cantidadEventos <= 4) {
          objeto.get()->getSonido().setVolume(30);
          cantidadEventos++;
        }
        Animacion &animacion = objeto.get()->getAnimacion();
        Area areaFondo = Area(
            objeto.get()->getX() - (this->car.get()->getX() - width / 2)
                - (float) objeto->getAnimacion().ancho() / 2.0f,
            objeto.get()->getY() - (this->car.get()->getY() - height / 2)
                - (float) objeto->getAnimacion().alto() / 2.0f,
            animacion.ancho(),
            animacion.alto());
        renderizador_.dibujar(animacion.get(iteracion),
                              areaFondo,
                              objeto.get()->getAngulo(),
                              false);
      }
    }
    if (objeto.get()->getAnimacion().terminoPrimerIteracion()) {
      pista.borrarEventoTemporal(idEventos[i]);
    }
  }
}

