#ifndef _EVENTO_GUI_H_
#define _EVENTO_GUI_H_

//Forward declarations
class EventoGUIHandler;

class EventoGUI {

public:
    virtual ~EventoGUI() {}
    virtual void actualizar(EventoGUIHandler& handler) = 0;
    
};

#endif
