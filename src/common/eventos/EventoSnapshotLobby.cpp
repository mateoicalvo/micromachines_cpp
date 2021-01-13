#include "includes/common/eventos/EventoSnapshotLobby.h"

#include "includes/common/Handler.h"

EventoSnapshotLobby::EventoSnapshotLobby(uint32_t uuidRemitente, Protocolo& protocolo) :
    Evento(uuidRemitente) {
    cantidadJugadores_ = protocolo.recibirNumUnsigned8();
    for (size_t i = 0; i < cantidadJugadores_; i++) {
        uint32_t idJugador = protocolo.recibirNumUnsigned32();
        //TODO: Que protocolo pueda enviar/recibir bool
        uint8_t estaListoRed = protocolo.recibirNumUnsigned8();
        bool estaListo = (estaListoRed == 1 ? true : false);
        idJugadorAEstaListo_.emplace(idJugador, estaListo);
    }
}

EventoSnapshotLobby::EventoSnapshotLobby(std::map<uint32_t, bool>&& datos) :
    Evento(0),
    cantidadJugadores_(datos.size()) {        
    
    UUIDEvento_ = UUID_EVENTO_SNAPSHOT_LOBBY;
    idJugadorAEstaListo_ = std::move(datos);
}

void EventoSnapshotLobby::enviarse(Protocolo& protocolo) {
    protocolo.enviar(UUIDEvento_);
    protocolo.enviar(cantidadJugadores_);
    for (const auto& kv : idJugadorAEstaListo_) {
        protocolo.enviar(kv.first);
        uint8_t estaListoRed = (kv.second ? 1 : 0);
        protocolo.enviar(estaListoRed);
    }
}

void EventoSnapshotLobby::actualizar(Handler& handler) {
    handler.manejar(*this);
}
