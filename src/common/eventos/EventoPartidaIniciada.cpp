#include "includes/common/eventos/EventoPartidaIniciada.h"

#include "includes/common/Handler.h"

EventoPartidaIniciada::EventoPartidaIniciada(uint32_t uuidRemitente, Protocolo& protocolo) :
    Evento(uuidRemitente),
    estadoInicial_(uuidRemitente, protocolo) {
        idDelVehiculo_ = protocolo.recibirNumUnsigned8();
}

EventoPartidaIniciada::EventoPartidaIniciada(uint8_t idDelVehiculo, std::map<uint8_t, datosVehiculo_>&& datos) :
    Evento(0),
    idDelVehiculo_(idDelVehiculo),
    estadoInicial_(std::move(datos)) {        
    UUIDEvento_ = UUID_EVENTO_PARTIDA_INICIADA;
}

void EventoPartidaIniciada::enviarse(Protocolo& protocolo) {
    protocolo.enviar(UUIDEvento_);
    estadoInicial_.enviarSoloDatos(protocolo);
    protocolo.enviar(idDelVehiculo_);
}

void EventoPartidaIniciada::actualizar(Handler& handler) {
    handler.manejar(*this);
}
