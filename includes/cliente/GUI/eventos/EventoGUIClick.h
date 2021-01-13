#ifndef _EVENTO_GUI_CLICK_H_
#define _EVENTO_GUI_CLICK_H_

#include "includes/cliente/GUI/eventos/EventoGUI.h"

class EventoGUIClick : public EventoGUI {
private:
    unsigned int x_;
    unsigned int y_;

public:
    EventoGUIClick(unsigned int x, unsigned int y);
    virtual void actualizar(EventoGUIHandler& handler) override;
};

#endif
