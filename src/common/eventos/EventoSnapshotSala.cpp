#include "includes/common/eventos/EventoSnapshotSala.h"

#include "includes/common/Handler.h"

EventoSnapshotSala::EventoSnapshotSala(uint32_t uuidRemitente, Protocolo& protocolo) :
    Evento(uuidRemitente) {
    cantidadPartidas_ = protocolo.recibirNumUnsigned16();
    for (uint16_t ordinal = 0; ordinal < cantidadPartidas_; ordinal++) {
        uint16_t uuidPartida = protocolo.recibirNumUnsigned16();
        ordinalAuuidPartida_.emplace(ordinal, uuidPartida);
    }
}

EventoSnapshotSala::EventoSnapshotSala(std::map<uint16_t, uint16_t>&& datos) :
    Evento(0),
    cantidadPartidas_(datos.size()) {        
    
    UUIDEvento_ = UUID_EVENTO_SNAPSHOT_SALA;
    ordinalAuuidPartida_ = std::move(datos);
}

void EventoSnapshotSala::enviarse(Protocolo& protocolo) {
    protocolo.enviar(UUIDEvento_);
    protocolo.enviar(cantidadPartidas_);
    for (const auto& kv : ordinalAuuidPartida_) {
        protocolo.enviar(kv.second);
    }
}

void EventoSnapshotSala::actualizar(Handler& handler) {
    handler.manejar(*this);
}
