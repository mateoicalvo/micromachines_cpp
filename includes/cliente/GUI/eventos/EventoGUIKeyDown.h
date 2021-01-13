#ifndef _EVENTO_GUI_KEY_DOWN_H_
#define _EVENTO_GUI_KEY_DOWN_H_

#include <string>

#include "includes/cliente/GUI/eventos/EventoGUI.h"

#define TECLA_ESC "Esc"
#define TECLA_C "c"
#define TECLA_A "a"
#define TECLA_Z "z"
#define TECLA_IZQ "Izq"
#define TECLA_DER "Der"
#define TECLA_FULLSCREEN "F11"

class EventoGUIKeyDown : public EventoGUI {
private:
    std::string tecla_;

public:
    EventoGUIKeyDown(const std::string& tecla);
    virtual void actualizar(EventoGUIHandler& handler) override;
    std::string& getTecla();
};

#endif
