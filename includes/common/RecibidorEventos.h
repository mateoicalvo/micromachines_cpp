#ifndef _RECIBIDOR_EVENTOS_H_
#define _RECIBIDOR_EVENTOS_H_

#include "includes/common/Hilo.h"
#include "includes/common/red/SocketTCP.h"
#include "includes/common/Cola.h"
#include "includes/common/eventos/Evento.h"
#include "includes/common/red/Protocolo.h"

class RecibidorEventos : public Hilo {
private:
    Cola<std::shared_ptr<Evento>>& destino_;
    Protocolo protocolo_;
    uint32_t UUIDRemitente_;
    
public:
    RecibidorEventos(SocketTCP& origen, Cola<std::shared_ptr<Evento>>& destino, uint32_t uuidRemitente);
    virtual void correr() override;
    virtual void detener() override;
};

#endif
