#ifndef _EVENTO_CREAR_PARTIDA_H_
#define _EVENTO_CREAR_PARTIDA_H_

#include "includes/common/eventos/Evento.h"
#include "includes/common/red/Protocolo.h"

class EventoCrearPartida : public Evento {
 public:
  EventoCrearPartida(uint32_t uuidRemitente, Protocolo &protocolo);
  EventoCrearPartida();
  virtual void enviarse(Protocolo &protocolo) override;
  virtual void actualizar(Handler &handler) override;
};

#endif
