#ifndef _PISTA_H_
#define _PISTA_H_
#include "includes/3rd-party/jsoncpp/json.hpp"
#include "includes/cliente/GUI/Animacion.h"
#include "includes/cliente/GUI/AnimacionFactory.h"
#include <map>
#include <memory>
#include <vector>
#include <mutex>
#include "includes/cliente/GUI/ObjetoDinamico.h"

class Pista {
 private:
  Renderizador &renderizador;
  uint16_t capas, size_x, size_y;
  std::map<int, std::vector<std::vector<std::shared_ptr<Animacion>>>> mapa;
  std::map<int, std::shared_ptr<Animacion>> texturas;
  std::map<int, std::shared_ptr<ObjetoDinamico>> objetosDinamicos;
  std::map<int, std::shared_ptr<ObjetoDinamico>> eventosTemporales;
  int idEventoTemporal;

  void agregarBloque(int capa, int x, int y, std::shared_ptr<Animacion> animacion);
  void crearPista(nlohmann::json pistaJson);

 public:
  Pista(std::string fileName, Renderizador &renderizador);
  std::shared_ptr<Animacion> getBloque(int capa, int x, int y) const;
  void agregarObjeto(int id, std::shared_ptr<ObjetoDinamico>);
  void agregarEventoTemporal(std::shared_ptr<ObjetoDinamico>);
  std::shared_ptr<ObjetoDinamico> obtenerObjeto(int id);
  std::shared_ptr<ObjetoDinamico> obtenerEventoTemporal(int id);
  void obtenerIds(std::vector<int> &ids);
  void obtenerIdsEventosTemporales(std::vector<int> &ids);
  void borrarObjeto(int id);
  void borrarEventoTemporal(int id);
  int getCapas() const;
  int getSizeX() const;
  int getSizeY() const;
};

#endif

