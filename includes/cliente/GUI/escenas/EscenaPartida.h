#ifndef _ESCENA_PARTIDA_H_
#define _ESCENA_PARTIDA_H_

#include "includes/cliente/GUI/escenas/Escena.h"

#include <memory>

#include "includes/common/ColaProtegida.h"
#include "includes/common/Conversor.h"
#include "includes/cliente/GUI/Animacion.h"
#include "includes/cliente/GUI/Area.h"
#include "includes/cliente/GUI/Renderizador.h"
#include "includes/cliente/GUI/Textura.h"
#include "includes/cliente/GUI/Pista.h"
#include "includes/cliente/GUI/Camara.h"
#include "includes/cliente/jugadores/Jugador.h"
#include "includes/cliente/jugadores/Computadora.h"


class EscenaPartida : public Escena {
 private:
  ColaProtegida<std::shared_ptr<EventoGUI>> &eventosGUI_;
  Pista pista;
  Conversor conversor;
  Camara camara;

  std::shared_ptr<Jugador> jugador_;
  int screenX, screenY;
  ObjetoDinamico barro;

  int id_car;
  bool barroActivo;
  void dibujarInterfaz(int iteracion);
  void dibujarBarro(int iteracion);
 public:
  EscenaPartida(Renderizador &renderizador,
                ColaProtegida<std::shared_ptr<EventoGUI>> &eventosGUI,
                std::stack<std::shared_ptr<Escena>> &escenas,
                ColaBloqueante<std::shared_ptr<Evento>> &eventosAEnviar_,
                EventoPartidaIniciada& estadoInicial,
                Sonido& musicaAmbiente,
                bool juegaComputadora);
  ~EscenaPartida();
  virtual Textura dibujate(uint32_t numeroIteracion, Area dimensiones) override;
  virtual void manejarInput(EventoGUI &evento) override;
  virtual void manejarInput(EventoGUIClick &evento) override;
  virtual void manejarInput(EventoGUIKeyDown &evento) override;
  virtual void manejarInput(EventoGUIKeyUp &evento) override;
  virtual void manejar(Evento &e) override;
  virtual void manejar(EventoSnapshot &e) override;
  virtual void manejar(EventoChoque &e) override ;
  virtual void manejar(EventoFrenada &e) override;
  virtual void manejar(EventoExplosion &e) override ;
  virtual void manejar(EventoBarroPisado &e) override ;
  virtual void manejar(EventoFinBarro &e) override ;
  virtual void manejar(EventoFinCarrera &e) override;
  virtual void manejar(EventoAparecioConsumible& e) override;
  virtual void manejar(EventoDesaparecioConsumible& e) override;
};
#endif
