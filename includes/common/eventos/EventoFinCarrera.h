#ifndef _EVENTO_FIN_CARRERA_H_
#define _EVENTO_FIN_CARRERA_H_

#include "includes/common/eventos/Evento.h"
#include "includes/common/red/Protocolo.h"

#include <vector>

class EventoFinCarrera : public Evento {
public:
    
    std::vector<uint8_t> podio_;

    EventoFinCarrera(uint32_t uuidRemitente, Protocolo& protocolo);
    EventoFinCarrera(std::vector<uint8_t>&& podio);
    virtual void enviarse(Protocolo& protocolo) override;
    virtual void actualizar(Handler& handler) override;
};

#endif
