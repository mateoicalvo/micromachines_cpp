#ifndef _ESCENA_PODIO_H_
#define _ESCENA_PODIO_H_

#include <includes/cliente/GUI/Animacion.h>
#include <includes/common/ColaProtegida.h>
#include <includes/cliente/GUI/ObjetoDinamico.h>
#include "includes/cliente/GUI/escenas/Escena.h"

typedef struct {
  double x_;
  double y_;
} area_t;

class EscenaPodio : public Escena {
 private:
  Animacion fondoMenu_;
  ColaProtegida<std::shared_ptr<EventoGUI>> &eventosGUI_;
  std::map<int, std::shared_ptr<ObjetoDinamico>> mapaAutos;
  std::map<int,area_t> areasPodio;

  void dibujarAutos(int nroIteracion);

 public:
  EscenaPodio(Renderizador &renderizador,
              ColaProtegida<std::shared_ptr<EventoGUI>> &eventosGUI,
              std::stack<std::shared_ptr<Escena>> &escenas,
              ColaBloqueante<std::shared_ptr<Evento>> &eventosAEnviar_,
              Sonido &musicaAmbiente,
              std::map<int, std::shared_ptr<ObjetoDinamico>> &mapaAutos);
  virtual Textura dibujate(uint32_t numeroIteracion, Area dimensiones) override;
  virtual void manejarInput(EventoGUI &evento) override;
  virtual void manejarInput(EventoGUIClick &evento) override;
  virtual void manejarInput(EventoGUIKeyDown &evento) override;
  virtual void manejarInput(EventoGUIKeyUp &evento) override;

  virtual void manejar(Evento &e) override;
};
#endif
