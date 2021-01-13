#include "includes/common/EnviadorEventos.h"

#include <iostream>

EnviadorEventos::EnviadorEventos(SocketTCP& socketDestino, ColaBloqueante<std::shared_ptr<Evento>>& origen) :
    origen_(origen),
    protocolo_(socketDestino) {
}

void EnviadorEventos::correr() {
    bool obtenido;
    std::shared_ptr<Evento> eventoAEnviar;
    while(seguirCorriendo_ && (obtenido = origen_.get(eventoAEnviar))) {
        try {
            eventoAEnviar->enviarse(protocolo_);
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << '\n';
            break;
        }        
    }
}

void EnviadorEventos::detener() {
    seguirCorriendo_ = false;
}
