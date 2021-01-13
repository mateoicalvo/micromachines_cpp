#ifndef __COMPUTADORA_H__
#define __COMPUTADORA_H__

#include <exception>
#include <string>
#include <atomic>

#include "includes/cliente/jugadores/Jugador.h"

#include "includes/common/Hilo.h"
#include "includes/3rd-party/lua/LuaInterprete.hpp"


class Computadora : public Jugador, Hilo {
private:
	LuaInterpreter lua;
	std::atomic<uint_least16_t> x_;
	std::atomic<uint_least16_t> y_;
	std::atomic<uint_least16_t> angulo_;
	int last_command_ = -1;
	void leave_command();
	void do_command();

public:
	Computadora(ColaBloqueante<std::shared_ptr<Evento>> &eventosAEnviar,
													 std::string fileName);

	virtual void setEstado(float x, float y, uint16_t angulo) override ;
	virtual void empezar() override ;
	virtual void terminar() override ;


	virtual void detener() override ;
	virtual void correr() override ;

// eventos humano
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
