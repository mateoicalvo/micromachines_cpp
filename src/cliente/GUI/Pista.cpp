#include "includes/cliente/GUI/Pista.h"
#include <fstream>

void Pista::agregarBloque(int capa,
                          int x,
                          int y,
                          std::shared_ptr<Animacion> animacion) {
  mapa[capa][x][y] = animacion;
}

void Pista::crearPista(nlohmann::json pistaJson) {
  for (uint16_t i = 0; i < size_x; i++) {
    for (uint16_t j = 0; j < size_y; j++) {
      int bloqueTerreno =
          pistaJson["capas"]["terreno"][std::to_string(i)][std::to_string(j)].get<
              int>();
      if (bloqueTerreno != -1) {
        if (texturas.find(bloqueTerreno) == texturas.end()) {
          texturas.insert(std::pair<int, std::shared_ptr<Animacion>>(
              bloqueTerreno,
              std::make_shared<Animacion>(AnimacionFactory::instanciar(
                  bloqueTerreno,
                  renderizador))));
        }
        agregarBloque(0, i, j, texturas.at(bloqueTerreno));
      }
    }
    for (uint16_t i = 0; i < size_x; i++) {
      for (uint16_t j = 0; j < size_y; j++) {
        int bloqueTerreno =
            pistaJson["capas"]["pista"][std::to_string(i)][std::to_string(j)].get<
                int>();
        if (bloqueTerreno != -1) {
          if (texturas.find(bloqueTerreno) == texturas.end()) {
            texturas.insert(std::pair<int, std::shared_ptr<Animacion>>(
                bloqueTerreno,
                std::make_shared<Animacion>(AnimacionFactory::instanciar(
                    bloqueTerreno,
                    renderizador))));
          }
          agregarBloque(1, i, j, texturas.at(bloqueTerreno));
        }
      }
    }
  }
}

Pista::Pista(std::string
             fileName, Renderizador &renderizador)
    : renderizador(renderizador), objetosDinamicos() {
  std::string rutaPista = fileName;
  std::ifstream archivoPista(rutaPista);
  Json pistaJson;
  archivoPista >> pistaJson;
  this->capas = pistaJson["dimensiones"]["capas"].get<uint16_t>();
  this->size_x = pistaJson["dimensiones"]["x"].get<uint16_t>();
  this->size_y = pistaJson["dimensiones"]["y"].get<uint16_t>();
  for (int i = 0; i < this->capas; i++) {
    std::vector<std::vector<std::shared_ptr<Animacion>>> matrix;
    for (int j = 0; j < this->size_x; j++) {
      std::vector<std::shared_ptr<Animacion>> array;
      for (int k = 0; k < this->size_y; k++) {
        array.emplace_back(nullptr);
      }
      matrix.push_back(array);
    }
    mapa.insert(std::pair<int,
                          std::vector<std::vector<std::shared_ptr<Animacion>>>>(
        i,
        matrix));
  }
  crearPista(pistaJson);
  idEventoTemporal = 0;
}

std::shared_ptr<Animacion> Pista::getBloque(int capa, int x, int y) const {
  return mapa.at(capa).at(x).at(y);
}

void Pista::agregarObjeto(int id,
                          std::shared_ptr<ObjetoDinamico> objetoDinamico) {
  objetosDinamicos.insert(std::pair<int, std::shared_ptr<ObjetoDinamico>>(id,
                                                                          objetoDinamico));
}

void Pista::agregarEventoTemporal(std::shared_ptr<ObjetoDinamico> eventoTemporal) {
  eventosTemporales.insert(std::pair<int, std::shared_ptr<ObjetoDinamico>>(
      idEventoTemporal,
      eventoTemporal));
  this->idEventoTemporal++;
}

std::shared_ptr<ObjetoDinamico> Pista::obtenerObjeto(int id) {
  if (objetosDinamicos.find(id) != objetosDinamicos.end()) {
    return objetosDinamicos.at(id);
  }
  return nullptr;
}

std::shared_ptr<ObjetoDinamico> Pista::obtenerEventoTemporal(int id) {
  return eventosTemporales.at(id);
}

void Pista::obtenerIds(std::vector<int> &ids) {
  for (std::map<int, std::shared_ptr<ObjetoDinamico>>::iterator
           it = objetosDinamicos.begin();
       it != objetosDinamicos.end(); ++it) {
    ids.push_back(it->first);
  }
}

void Pista::obtenerIdsEventosTemporales(std::vector<int> &ids) {
  for (std::map<int, std::shared_ptr<ObjetoDinamico>>::iterator
           it = eventosTemporales.begin();
       it != eventosTemporales.end(); ++it) {
    ids.push_back(it->first);
  }
}

void Pista::borrarObjeto(int id) {
  if (objetosDinamicos.find(id) != objetosDinamicos.end()) {
    objetosDinamicos.erase(id);
  }
}

void Pista::borrarEventoTemporal(int id) {
  eventosTemporales.erase(id);
}

int Pista::getCapas() const {
  return capas;
}

int Pista::getSizeX() const {
  return size_x;
}

int Pista::getSizeY() const {
  return size_y;
}
