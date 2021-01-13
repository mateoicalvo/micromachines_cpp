#ifndef __JUGADOR_H__
#define __JUGADOR_H__

#include <memory>
#include "includes/common/ColaBloqueante.h"
#include "includes/common/eventos/Evento.h"
#include "includes/common/eventos/EventoAcelerar.h"
#include "includes/common/eventos/EventoDesacelerar.h"
#include "includes/common/eventos/EventoDoblarDerecha.h"
#include "includes/common/eventos/EventoDejarDeDoblarDerecha.h"
#include "includes/common/eventos/EventoDoblarIzquierda.h"
#include "includes/common/eventos/EventoDejarDeDoblarIzquierda.h"
#include "includes/common/eventos/EventoFrenar.h"
#include "includes/common/eventos/EventoDejarDeFrenar.h"


class Jugador {
private:
	ColaBloqueante<std::shared_ptr<Evento>> &eventosAEnviar_;
public:
	Jugador(ColaBloqueante<std::shared_ptr<Evento>> &eventosAEnviar);

	virtual void setEstado(float x, float y, uint16_t angulo);
	virtual void empezar();
	virtual void terminar();


	virtual void acelerar();

	virtual void desacelerar();

	virtual void frenar();

	virtual void dejarDeFrenar();

	virtual void doblarDerecha();

	virtual void dejarDeDoblarDerecha();

	virtual void doblarIzquierda();

	virtual void dejarDeDoblarIzquierda();
};


#endif
