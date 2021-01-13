#include "includes/common/red/SocketTCP.h"

//#define _POSIX_C_SOURCE 200112L

#include <unistd.h>
#include <stdexcept>
#include <string.h>

SocketTCP::SocketTCP(int unFileDescriptor) :
    fileDescripor_(unFileDescriptor),
    hints_(nullptr) {
}

SocketTCP::SocketTCP(const std::string& unHost, const std::string& unPuerto) :
    fileDescripor_(-1),
    hints_(nullptr) {
    int status = 0;
    addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = IP_VERSION;    
    hints.ai_socktype = SOCKET_TYPE;
    hints.ai_flags = AI_PASSIVE;
    status = getaddrinfo(unHost.c_str(), unPuerto.c_str(), &hints, &hints_);
    if (status != 0) { 
        throw std::runtime_error(ERROR_GET_ADDRINFO);
    }
    fileDescripor_ = socket(hints_->ai_family, hints_->ai_socktype, hints_->ai_protocol);
    if (fileDescripor_ == -1) {
        throw std::runtime_error(ERROR_CREAR);
    }
}

SocketTCP::SocketTCP(SocketTCP&& otro) {
    hints_ = otro.hints_;
    fileDescripor_ = otro.fileDescripor_;
    otro.hints_ = nullptr;
    otro.fileDescripor_ = -1;
}

SocketTCP& SocketTCP::operator=(SocketTCP&& otro) {
    if (this == &otro) {
        return *this;
    }
    if (hints_) {
        freeaddrinfo(hints_);
    }
    if (fileDescripor_ != -1) {
        close(fileDescripor_);
    }
    hints_ = otro.hints_;
    fileDescripor_ = otro.fileDescripor_;    
    otro.hints_ = nullptr;
    otro.fileDescripor_ = -1;    
    return *this;
}

void SocketTCP::cerrarLectoEscritura() {
    shutdown(fileDescripor_, SHUT_RDWR);
}

size_t SocketTCP::enviarN(const char* buffer, size_t nBytes) {
    size_t enviados = 0;
    int s = 0;
    while (enviados < nBytes) {
        s = send(fileDescripor_, &buffer[enviados],
            nBytes - enviados, MSG_NOSIGNAL);

        if (s < 0) {
            throw std::runtime_error(ERROR_SEND);
        } else if (s == 0) {
            throw std::runtime_error(ERROR_CERRADO_S);
        } else {
            enviados += s;                       
        }
    }
    return enviados;
}

size_t SocketTCP::recibirN(char* buffer, size_t nBytes) {
    size_t recibidos = 0;
    int  s = 0;
    while (recibidos < nBytes) {
        s = recv(fileDescripor_, &buffer[recibidos],
            nBytes - recibidos, 0);
        if (s < 0) {
            throw std::runtime_error(ERROR_RECV);
        } else if (s == 0) {
            throw std::runtime_error(ERROR_CERRADO_R);
        } else {
            recibidos += s;                       
        }
    }
    return recibidos;
}

SocketTCP::~SocketTCP() {
    if (fileDescripor_ != -1) {
        close(fileDescripor_);
    }
    if (hints_) {
        freeaddrinfo(hints_);
    }
}
