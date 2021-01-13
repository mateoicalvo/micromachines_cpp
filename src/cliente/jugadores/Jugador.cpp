#include "includes/cliente/jugadores/Jugador.h"

Jugador::Jugador(ColaBloqueante<std::shared_ptr<Evento>> &eventosAEnviar)
										 : eventosAEnviar_(eventosAEnviar) {}

 void Jugador::setEstado(float x, float y, uint16_t angulo){}
 void Jugador::empezar(){}
 void Jugador::terminar(){}


 void Jugador::acelerar(){
   std::shared_ptr<Evento>
    	eventoAcelerar = std::make_shared<EventoAcelerar>();
	eventosAEnviar_.put(eventoAcelerar);
}

 void Jugador::desacelerar(){
    std::shared_ptr<Evento>
    	eventoDesacelerar = std::make_shared<EventoDesacelerar>();
	eventosAEnviar_.put(eventoDesacelerar);
}

 void Jugador::frenar(){
	std::shared_ptr<Evento>
        eventoFrenar = std::make_shared<EventoFrenar>();
	eventosAEnviar_.put(eventoFrenar);
}

 void Jugador::dejarDeFrenar(){
	std::shared_ptr<Evento>
		eventoDejarDeFrenar = std::make_shared<EventoDejarDeFrenar>();
	eventosAEnviar_.put(eventoDejarDeFrenar);
}

 void Jugador::doblarDerecha(){
	std::shared_ptr<Evento>
        eventoDoblarDerecha = std::make_shared<EventoDoblarDerecha>();
	eventosAEnviar_.put(eventoDoblarDerecha);
}

 void Jugador::dejarDeDoblarDerecha(){
	std::shared_ptr<Evento>
		eventoDejarDeDoblarDerecha = std::make_shared<EventoDejarDeDoblarDerecha>();
	eventosAEnviar_.put(eventoDejarDeDoblarDerecha);
}

 void Jugador::doblarIzquierda(){
	std::shared_ptr<Evento>
        eventoDoblarIzquierda = std::make_shared<EventoDoblarIzquierda>();
	eventosAEnviar_.put(eventoDoblarIzquierda);
}

 void Jugador::dejarDeDoblarIzquierda(){
	std::shared_ptr<Evento>
		eventoDejarDeDoblarIzquierda = std::make_shared<EventoDejarDeDoblarIzquierda>();
	eventosAEnviar_.put(eventoDejarDeDoblarIzquierda);
}
