#ifndef _EVENTO_GUI_HANDLER_H_
#define _EVENTO_GUI_HANDLER_H_

#include "includes/cliente/GUI/eventos/EventoGUI.h"
#include "includes/cliente/GUI/eventos/EventoGUIClick.h"
#include "includes/cliente/GUI/eventos/EventoGUIKeyDown.h"
#include "includes/cliente/GUI/eventos/EventoGUIKeyUp.h"

class EventoGUIHandler {

public:
    virtual void manejarInput(EventoGUI& evento) = 0;
    virtual void manejarInput(EventoGUIClick& evento) = 0;
    virtual void manejarInput(EventoGUIKeyDown& evento) = 0;
    virtual void manejarInput(EventoGUIKeyUp& evento) = 0;
};

#endif
