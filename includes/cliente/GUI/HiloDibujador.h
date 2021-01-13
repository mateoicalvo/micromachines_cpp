#ifndef _HILO_DIBUJADOR_H_
#define _HILO_DIBUJADOR_H_

#include "includes/common/Hilo.h"

#include <stack>
#include <memory>
#include <includes/common/ColaBloqueante.h>

#include "includes/common/eventos/Evento.h"
#include "includes/common/ColaProtegida.h"
#include "includes/cliente/GUI/Sonido.h"
#include "includes/cliente/GUI/Ventana.h"
#include "includes/cliente/GUI/Renderizador.h"
#include "includes/cliente/GUI/eventos/EventoGUI.h"
#include "includes/cliente/grabador/HiloGrabador.h"

class HiloDibujador : public Hilo {
 private:
  Ventana &ventana_;
  Renderizador &renderizador_;
  HiloGrabador &grabador_;
  ColaProtegida<std::shared_ptr<Evento>> eventos_;
  ColaProtegida<std::shared_ptr<EventoGUI>> &eventosGUI_;
  ColaBloqueante<std::shared_ptr<Evento>> &eventosAEnviar_;
  //TODO: Abstraer en "Escenario" ?
  std::stack<std::shared_ptr<Escena>> escenas_;
  Sonido musicaAmbiente;
  bool &seguirCorriendoCliente;
  void step(uint32_t nroIteracion, Escena &escena);
 public:
  HiloDibujador(Ventana &ventana,
                Renderizador &renderizador,
                HiloGrabador &grabador,
                ColaProtegida<std::shared_ptr<EventoGUI>> &eventosGUI,
                ColaBloqueante<std::shared_ptr<Evento>> &eventosAEnviar_,
                bool &seguirCorriendo);
  virtual void correr() override;
  virtual void detener() override;

  ColaProtegida<std::shared_ptr<Evento>> &eventosEntrantes();
};

#endif
