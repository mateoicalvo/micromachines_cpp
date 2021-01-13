#ifndef _ESCENA_H_
#define _ESCENA_H_

#include <stack>
#include <memory>
#include <includes/common/ColaBloqueante.h>
#include <includes/cliente/GUI/Sonido.h>

#include "includes/cliente/GUI/EventoGUIHandler.h"

#include "includes/cliente/GUI/Renderizador.h"
#include "includes/cliente/GUI/Textura.h"

#include "includes/common/Handler.h"

class Escena : public EventoGUIHandler, public Handler {
 protected:
  std::stack<std::shared_ptr<Escena>> &escenas_;
  Renderizador &renderizador_;
  ColaBloqueante<std::shared_ptr<Evento>> &eventosAEnviar_;
  Sonido &musicaAmbiente;

 public:
  Escena(std::stack<std::shared_ptr<Escena>> &escenas,
         Renderizador &renderizador,
         ColaBloqueante<std::shared_ptr<Evento>> &eventosAEnviar_,
         Sonido &musicaAmbiente);
  virtual Textura dibujate(uint32_t numeroIteracion, Area dimensiones) = 0;
  virtual ~Escena();
};

#endif
