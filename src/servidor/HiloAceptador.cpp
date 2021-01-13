#include "includes/servidor/HiloAceptador.h"

#include <iostream>

#include "includes/servidor/utils/ConfigServidor.h"

HiloAceptador::HiloAceptador(const std::string& unHost, const std::string& puerto, SalaDeEspera& salaDeEspera) :
    sktAceptador_(unHost, puerto),
    salaDeEspera_(salaDeEspera) {
}

void HiloAceptador::correr() {
    try {
    sktAceptador_.enlazar();
    sktAceptador_.escuchar(CONFIG_SERVIDOR.maxClientesEnEspera());
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    while (seguirCorriendo_) {
        try {
            SocketTCP aceptado = sktAceptador_.aceptar();
            salaDeEspera_.agregarJugador(std::move(aceptado));
        }
        catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
        }
    }
}

void HiloAceptador::detener() {
    seguirCorriendo_ = false;
    sktAceptador_.cerrarLectoEscritura();
}

HiloAceptador::~HiloAceptador() {
}
