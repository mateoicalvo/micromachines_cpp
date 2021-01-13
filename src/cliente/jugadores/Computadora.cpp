#include <fstream>

#include "includes/cliente/jugadores/Computadora.h"

#include "includes/3rd-party/jsoncpp/json.hpp"
#include "includes/cliente/utils/ConfigCliente.h"
#include "includes/common/Cronometro.h"


Computadora::Computadora(ColaBloqueante<std::shared_ptr<Evento>> &eventosAEnviar,
												 std::string fileName) :
														 Jugador(eventosAEnviar){
  	std::string rutaPista = std::move(fileName);
	std::ifstream archivoPista(rutaPista);
	Json pistaJson;
	archivoPista >> pistaJson;

    int size_x = pistaJson["dimensiones"]["x"].get<uint16_t>();
		int size_y = pistaJson["dimensiones"]["y"].get<uint16_t>(); 

	lua.init_script(CONFIG_CLIENTE.rutaLuaScript().c_str());
    for (uint16_t i = 0; i < size_x; i++) {
      for (uint16_t j = 0; j < size_y; j++) {
      		int x = i;
      		int y = size_y - j - 1;
	        if (pistaJson["capas"]["pista"][std::to_string(i)][std::to_string(j)].get<int>() > 0){
				lua.get_function_name("insert_road_block");
	        	lua << x;
	        	lua << y; 	
	    		lua.call_function("insert_road_block", 2, 0);
	        } else {
				lua.get_function_name("insert_bad_block");
	        	lua << x;
	        	lua << y; 	
	    		lua.call_function("insert_bad_block", 2, 0);
	        }
		}
	}

}

void Computadora::setEstado(float x, float y, uint16_t angulo){
	x_ = (uint16_t) x * 100;
	y_ = (uint16_t) y * 100;
	angulo_ = angulo;		
}
void Computadora::empezar(){
	Hilo::iniciar();
}

void Computadora::terminar(){
	detener();
	Hilo::join();
}

void Computadora::detener(){
	this->seguirCorriendo_ = false;
}

void Computadora::correr(){
	lua.init_script(CONFIG_CLIENTE.rutaLuaScriptUsuario().c_str());
	double frecuencia = (double) 1 / (double) CONFIG_CLIENTE.tiempoReaccionHumano();
    int iteracion = 0;
    frecuencia *= 1000;
    Cronometro c;
    double t1 = c.ahora();				
		
	while (seguirCorriendo_){
		lua.get_function_name("get_instruction");
		int x = std::floor(x_ /1000.0f);
		int y = std::floor(y_/1000.0f);
		uint16_t angulo = angulo_;
		lua << (int) x;
		lua << (int) y;
		lua << (int) angulo;
		lua.call_function("get_instruction", 3, 1);
		do_command();
		double t2 = c.ahora();
        double resto = frecuencia - (t2 - t1);
        if (resto < 0) {
          double atraso = -resto;
          double perdidos = atraso - std::fmod(atraso, frecuencia);
          resto = frecuencia - std::fmod(atraso, frecuencia);
          t1 += perdidos;
          iteracion += std::floor(perdidos / frecuencia);
        }
        Hilo::dormir(resto);
        t1 += frecuencia;
        iteracion += 1;
	}
}

void Computadora::do_command(){
	int command  = lua.get<int>();
	if (command != last_command_){
		leave_command();
	}
	if (command == 0){
		Jugador::doblarDerecha();
	} else if (command == 1){
		Jugador::acelerar();
	} else if (command == 2){
		Jugador::doblarIzquierda();
	} else if (command == 3){
		Jugador::frenar();
	}
	last_command_ = command;
}


void Computadora::leave_command(){
	if (last_command_ == 0){
		Jugador::dejarDeDoblarDerecha();
	} else if (last_command_ == 1){
		Jugador::desacelerar();
	} else if (last_command_ == 2){
		Jugador::dejarDeDoblarIzquierda();
	} else if (last_command_ == 3){
		Jugador::dejarDeFrenar();
	} else {}
}



// eventos humano
void Computadora::acelerar(){}
void Computadora::desacelerar(){}
void Computadora::frenar(){}
void Computadora::dejarDeFrenar(){}
void Computadora::doblarDerecha(){}
void Computadora::dejarDeDoblarDerecha(){}
void Computadora::doblarIzquierda(){}
void Computadora::dejarDeDoblarIzquierda(){}
