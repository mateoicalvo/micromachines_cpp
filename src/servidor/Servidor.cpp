#include "includes/servidor/Servidor.h"

#include <iostream>

Servidor::Servidor(const std::string& unHost, const std::string& puerto) :
    salaDeEspera_(eventosRecibidos_),
    hiloAceptador_(unHost, puerto, salaDeEspera_),
    distribuidorEventos_(eventosRecibidos_, salaDeEspera_, coordinadorPartidas_),
    coordinadorPartidas_(salaDeEspera_) {
}

void Servidor::correr() {
    hiloAceptador_.iniciar();
    distribuidorEventos_.iniciar();
    char c;
    while ((c = std::cin.get()) != CARACTER_SALIR) {
        // pass
    }
}

void Servidor::cerrar() {
    eventosRecibidos_.detener();

    hiloAceptador_.detener();
    hiloAceptador_.join();

    distribuidorEventos_.detener();
    distribuidorEventos_.join();
}
