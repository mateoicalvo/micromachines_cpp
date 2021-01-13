#ifndef _CAMARA_H_
#define _CAMARA_H_
#include <memory>
#include <vector>
#include "includes/common/Conversor.h"
#include "includes/cliente/GUI/ObjetoDinamico.h"
#include "includes/cliente/GUI/Pista.h"

class Camara {
 private:
  Conversor &conversor;
  Pista &pista;
  Renderizador& renderizador_;
  int width, height, xInicial, xFinal, yInicial, yFinal;
  std::shared_ptr<ObjetoDinamico> car;

 public:
  Camara(Conversor &conversor, Pista &pista,Renderizador& renderizador);
  void setWidthHeight(int width, int height);
  void setCar(std::shared_ptr<ObjetoDinamico> car);
  void dibujarPista(int iteracion);
  void dibujarObjetos(int car_id, int iteracion);
  void dibujarEventosTemporales(int iteracion);
};

#endif
