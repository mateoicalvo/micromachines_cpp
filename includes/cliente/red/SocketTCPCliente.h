#ifndef _SOCKET_TCP_CLIENTE_H_
#define _SOCKET_TCP_CLIENTE_H_

#include "includes/common/red/SocketTCP.h"

#include <string>

#define ERROR_CONEXION "Error al intentar conectar el socket."

class SocketTCPCliente : public SocketTCP {
public:
    SocketTCPCliente(const std::string& unHost, const std::string& unPuerto);

    void conectar();
};

#endif
