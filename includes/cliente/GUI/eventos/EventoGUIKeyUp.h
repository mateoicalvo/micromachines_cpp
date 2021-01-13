#ifndef _EVENTO_GUI_KEY_UP_H_
#define _EVENTO_GUI_KEY_UP_H_

#include <string>

#include "includes/cliente/GUI/eventos/EventoGUI.h"

#define TECLA_C "c"
#define TECLA_A "a"
#define TECLA_Z "z"
#define TECLA_IZQ "Izq"
#define TECLA_DER "Der"

class EventoGUIKeyUp: public EventoGUI {
 private:
  std::string tecla_;

 public:
  EventoGUIKeyUp(const std::string& tecla);
  virtual void actualizar(EventoGUIHandler& handler) override;
  std::string& getTecla();
};

#endif
