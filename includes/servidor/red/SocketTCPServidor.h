#ifndef _SOCKET_TCP_SERVIDOR_H_
#define _SOCKET_TCP_SERVIDOR_H_

#include "includes/common/red/SocketTCP.h"

#define ERROR_SET_SOCK_OPT "Error al llamar a setsockopt antes de enlazar."
#define ERROR_BIND "Error al intentar enlazar el socket."
#define ERROR_LISTEN "Error al llamar a listen()."
#define ERROR_ACEPTAR "Error al llamar a accept()."

class SocketTCPServidor : public SocketTCP {
public:
    SocketTCPServidor(const std::string& unHost, const std::string& unPuerto);

    void enlazar();

    void escuchar(unsigned int maxEnEspera);

    SocketTCP aceptar();
};

#endif
