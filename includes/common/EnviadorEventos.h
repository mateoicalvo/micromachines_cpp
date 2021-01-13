#ifndef _ENVIADOR_EVENTOS_H_
#define _ENVIADOR_EVENTOS_H_

#include "includes/common/Hilo.h"
#include "includes/common/red/SocketTCP.h"
#include "includes/common/ColaBloqueante.h"
#include "includes/common/eventos/Evento.h"
#include "includes/common/red/Protocolo.h"

class EnviadorEventos : public Hilo {
private:
    ColaBloqueante<std::shared_ptr<Evento>>& origen_;
    Protocolo protocolo_;

public:
    EnviadorEventos(SocketTCP& socketDestino, ColaBloqueante<std::shared_ptr<Evento>>& origen);
    virtual void correr() override;
    virtual void detener() override;
};

#endif
