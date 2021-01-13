#ifndef _ESCENA_SALA_H_
#define _ESCENA_SALA_H_

#include "includes/cliente/GUI/escenas/Escena.h"

#include <memory>

#include "includes/common/ColaProtegida.h"
#include "includes/cliente/GUI/Animacion.h"
#include "includes/cliente/GUI/Area.h"
#include "includes/cliente/GUI/Renderizador.h"
#include "includes/cliente/GUI/Textura.h"
#include "includes/cliente/GUI/Boton.h"

class EscenaSala : public Escena {
 private:
  Animacion fondoMenu_;
  //TODO: Mover a Escena
  ColaProtegida<std::shared_ptr<EventoGUI>> &eventosGUI_;
  std::map<int, std::shared_ptr<Boton>> botones;
  std::map<int, std::shared_ptr<Texto>> textoPartidas;
  std::map<uint16_t, uint16_t> partidasId;
  int partidaSeleccionada;
  uint16_t inicioVentana_;
  uint16_t finVentana_;

  void inicializarBotones();
  void inicializarTextoPartidas();
  void dibujarBotones(int iteracion);
  void dibujarTextoPartidas(int iteracion);
  void handlerBotones(int uuid);

 public:
  EscenaSala(Renderizador &renderizador,
             ColaProtegida<std::shared_ptr<EventoGUI>> &eventosGUI,
             std::stack<std::shared_ptr<Escena>> &escenas,
             ColaBloqueante<std::shared_ptr<Evento>> &eventosAEnviar_,
             Sonido &musicaAmbiente,
             EventoSnapshotSala& e);
  virtual Textura dibujate(uint32_t numeroIteracion, Area dimensiones) override;
  virtual void manejarInput(EventoGUI &evento) override;
  virtual void manejarInput(EventoGUIClick &evento) override;
  virtual void manejarInput(EventoGUIKeyDown &evento) override;
  virtual void manejarInput(EventoGUIKeyUp &evento) override;
  
  virtual void manejar(Evento &e) override;
  virtual void manejar(EventoSnapshotSala &e) override;
  virtual void manejar(EventoPartidaCreada& e) override;
  virtual void manejar(EventoSnapshotLobby& e) override;
};

#endif
