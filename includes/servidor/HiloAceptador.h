#ifndef _HILO_ACEPTADOR_H_
#define _HILO_ACEPTADOR_H_

#include <string>

#include "includes/common/Hilo.h"
#include "includes/common/red/SocketTCP.h"
#include "includes/servidor/red/SocketTCPServidor.h"
#include "includes/servidor/SalaDeEspera.h"

class HiloAceptador : public Hilo {

private:
    SocketTCPServidor sktAceptador_;
    SalaDeEspera& salaDeEspera_;

    HiloAceptador(const HiloAceptador& otro) = delete;
    HiloAceptador(HiloAceptador&& otro) = delete;
    HiloAceptador& operator=(HiloAceptador&& otro) = delete;    
    HiloAceptador& operator=(const HiloAceptador& otro) = delete;
    
public:
    HiloAceptador(const std::string& unHost, const std::string& puerto, SalaDeEspera& salaDeEspera);

    ~HiloAceptador();

    virtual void correr() override;
    virtual void detener() override;
};

#endif
