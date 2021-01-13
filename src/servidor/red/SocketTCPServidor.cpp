#include "includes/servidor/red/SocketTCPServidor.h"

#include <stdexcept>

SocketTCPServidor::SocketTCPServidor(const std::string& unHost, const std::string& unPuerto) :
    SocketTCP(unHost, unPuerto) {
}

void SocketTCPServidor::enlazar() {
    int opt_val = 1;
    int result_set_opt = setsockopt(fileDescripor_, SOL_SOCKET, \
        SO_REUSEADDR, &opt_val, sizeof(opt_val));
    if (result_set_opt == -1) {
        throw std::runtime_error(ERROR_SET_SOCK_OPT);
    }
    int status = -1;
    bool ok = false;
    for (struct addrinfo* rp = hints_; rp != NULL; rp = rp->ai_next) {
        status = bind(fileDescripor_, rp->ai_addr, rp->ai_addrlen);
        if (status == 0) {
            ok = true;
            break;
        }
    }
    if (!ok) {
        throw std::runtime_error(ERROR_BIND);
    }
}

void SocketTCPServidor::escuchar(unsigned int maxEnEspera) {
    int estado = listen(fileDescripor_, maxEnEspera);
    if (estado == -1) {
        throw std::runtime_error(ERROR_LISTEN);
    }
}

SocketTCP SocketTCPServidor::aceptar() {
    int fdAceptado = accept(fileDescripor_, NULL, NULL);
    if (fdAceptado == -1) {
        throw std::runtime_error(ERROR_ACEPTAR);
    }
    return std::move(SocketTCP(fdAceptado));
}
