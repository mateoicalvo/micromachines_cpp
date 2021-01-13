#include "includes/common/eventos/EventoFinCarrera.h"

#include "includes/common/Handler.h"

EventoFinCarrera::EventoFinCarrera(std::vector<uint8_t>&& podio) :
    Evento(0) {
    UUIDEvento_ = UUID_EVENTO_FIN_CARRERA;
    podio_ = std::move(podio);
}

EventoFinCarrera::EventoFinCarrera(uint32_t uuidRemitente, Protocolo &protocolo) :
    Evento(uuidRemitente) {
  uint8_t cantidad = protocolo.recibirNumUnsigned8();
  for (uint8_t i = 0; i < cantidad; ++i) {
    uint8_t idVehiculo = protocolo.recibirNumUnsigned8();
    podio_.emplace_back(idVehiculo);
  }
}

void EventoFinCarrera::enviarse(Protocolo &protocolo) {
  protocolo.enviar(UUIDEvento_);
  protocolo.enviar((uint8_t)podio_.size());
  for (uint8_t idVehiculo: podio_) {
    protocolo.enviar(idVehiculo);
  }
}

void EventoFinCarrera::actualizar(Handler &handler) {
  handler.manejar(*this);
}
