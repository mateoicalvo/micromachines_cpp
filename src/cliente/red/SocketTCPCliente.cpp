#include "includes/cliente/red/SocketTCPCliente.h"

#include <stdexcept>

SocketTCPCliente::SocketTCPCliente(const std::string& unHost, const std::string& unPuerto) :
    SocketTCP(unHost, unPuerto) {
}

void SocketTCPCliente::conectar() {
    bool conectado = false;
    int estado = -1;
    addrinfo* ptr = hints_;
    while (ptr != NULL && !conectado) {
        estado = connect(fileDescripor_, hints_->ai_addr, hints_->ai_addrlen);
        conectado = (estado != -1);
        ptr = ptr->ai_next;
    }
    if (!conectado) {
        throw std::runtime_error(ERROR_CONEXION);
    }

}
