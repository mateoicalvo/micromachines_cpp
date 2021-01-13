#ifndef _DISTRIBUIDOR_EVENTOS_H_
#define _DISTRIBUIDOR_EVENTOS_H_

#include "includes/common/Hilo.h"
#include "includes/common/Handler.h"
#include "includes/servidor/SalaDeEspera.h"
#include "includes/servidor/CoordinadorPartidas.h"
#include "includes/common/ColaBloqueante.h"
#include "includes/common/eventos/Evento.h"

class DistribuidorEventos : public Hilo, public Handler {
private:
    ColaBloqueante<std::shared_ptr<Evento>>& eventos_;
    SalaDeEspera& salaDeEspera_;
    CoordinadorPartidas& coordinadorPartidas_;

    DistribuidorEventos(const DistribuidorEventos& otro) = delete;
    DistribuidorEventos(DistribuidorEventos&& otro) = delete;
    DistribuidorEventos& operator=(DistribuidorEventos&& otro) = delete;    
    DistribuidorEventos& operator=(const DistribuidorEventos& otro) = delete;

public:
    DistribuidorEventos(ColaBloqueante<std::shared_ptr<Evento>>& eventos, SalaDeEspera& salaDeEspera, CoordinadorPartidas& coordinadorPartidas);

    ~DistribuidorEventos();

    virtual void correr() override;
    virtual void detener() override;

    virtual void manejar(Evento& e) override;

    virtual void manejar(EventoAcelerar& e) override;
    virtual void manejar(EventoDesacelerar& e) override;
    virtual void manejar(EventoFrenar& e) override;
    virtual void manejar(EventoDejarDeFrenar& e) override;
    virtual void manejar(EventoDoblarIzquierda& e) override;
    virtual void manejar(EventoDejarDeDoblarIzquierda& e) override;
    virtual void manejar(EventoDoblarDerecha& e) override;
    virtual void manejar(EventoDejarDeDoblarDerecha& e) override;
    virtual void manejar(EventoCrearPartida& e) override;
    virtual void manejar(EventoUnirseAPartida& e) override;
    virtual void manejar(EventoIniciarPartida& e) override;
    virtual void manejar(EventoUnirseASala& e) override;
    virtual void manejar(EventoDesconexion& e) override;
};

#endif
