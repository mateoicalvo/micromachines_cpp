#ifndef _HANDLER_H_
#define _HANDLER_H_

#include "includes/common/eventos/Evento.h"
#include "includes/common/eventos/EventoAcelerar.h"
#include "includes/common/eventos/EventoDesacelerar.h"
#include "includes/common/eventos/EventoFrenar.h"
#include "includes/common/eventos/EventoDejarDeFrenar.h"
#include "includes/common/eventos/EventoDoblarIzquierda.h"
#include "includes/common/eventos/EventoDejarDeDoblarIzquierda.h"
#include "includes/common/eventos/EventoDoblarDerecha.h"
#include "includes/common/eventos/EventoDejarDeDoblarDerecha.h"
#include "includes/common/eventos/EventoSnapshot.h"
#include "includes/common/eventos/EventoCrearPartida.h"
#include "includes/common/eventos/EventoUnirseAPartida.h"
#include "includes/common/eventos/EventoIniciarPartida.h"
#include "includes/common/eventos/EventoPartidaIniciada.h"
#include "includes/common/eventos/EventoDesconexion.h"
#include "includes/common/eventos/EventoFinCarrera.h"
#include "includes/common/eventos/EventoAparecioConsumible.h"
#include "includes/common/eventos/EventoDesaparecioConsumible.h"
#include "includes/common/eventos/EventoChoque.h"
#include "includes/common/eventos/EventoBarroPisado.h"
#include "includes/common/eventos/EventoExplosion.h"
#include "includes/common/eventos/EventoFinBarro.h"
#include "includes/common/eventos/EventoPartidaCreada.h"
#include "includes/common/eventos/EventoSnapshotLobby.h"
#include "includes/common/eventos/EventoSnapshotSala.h"
#include "includes/common/eventos/EventoUnirseASala.h"
#include "includes/common/eventos/EventoFrenada.h"

class Handler {
 public:
  virtual ~Handler();
  
  virtual void manejar(Evento &e) = 0;
  virtual void manejar(EventoAcelerar &e);
  virtual void manejar(EventoDesacelerar &e);
  virtual void manejar(EventoFrenar &e);
  virtual void manejar(EventoDejarDeFrenar &e);
  virtual void manejar(EventoDoblarIzquierda &e);
  virtual void manejar(EventoDejarDeDoblarIzquierda &e);
  virtual void manejar(EventoDoblarDerecha &e);
  virtual void manejar(EventoDejarDeDoblarDerecha &e);
  virtual void manejar(EventoSnapshot &e);
  virtual void manejar(EventoCrearPartida &e);
  virtual void manejar(EventoUnirseAPartida &e);
  virtual void manejar(EventoIniciarPartida &e);
  virtual void manejar(EventoPartidaIniciada &e);
  virtual void manejar(EventoFinCarrera &e);
  virtual void manejar(EventoAparecioConsumible &e);
  virtual void manejar(EventoDesaparecioConsumible &e);
  virtual void manejar(EventoDesconexion &e);
  virtual void manejar(EventoChoque &e);
  virtual void manejar(EventoBarroPisado &e);
  virtual void manejar(EventoExplosion &e);
  virtual void manejar(EventoFinBarro &e);
  virtual void manejar(EventoPartidaCreada &e);
  virtual void manejar(EventoSnapshotLobby &e);
  virtual void manejar(EventoSnapshotSala &e);
  virtual void manejar(EventoUnirseASala &e);
  virtual void manejar(EventoFrenada &e);
};

#endif
