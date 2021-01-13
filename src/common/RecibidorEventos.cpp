#include "includes/common/RecibidorEventos.h"

#include <iostream>

#include "includes/common/eventos/EventoFactory.h"
#include "includes/common/excepciones/EventoDesconocidoError.h"

RecibidorEventos::RecibidorEventos(SocketTCP& socketOrigen, Cola<std::shared_ptr<Evento>>& destino, uint32_t uuidRemitente) :
    destino_(destino),
    protocolo_(socketOrigen),
    UUIDRemitente_(uuidRemitente) {
}

void RecibidorEventos::correr() {
    while(seguirCorriendo_) {
        try {
            std::shared_ptr<Evento> eventoRecibido(EventoFactory::instanciar(UUIDRemitente_, protocolo_));
            destino_.put(eventoRecibido);
        }
        catch(EventoDesconocidoError& e) {
            std::cerr << e.what() << '\n';
            continue;
        }
        catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
            std::shared_ptr<Evento> desconexion(std::make_shared<EventoDesconexion>(UUIDRemitente_));
            destino_.put(desconexion);
            break;
        }
    }
}

void RecibidorEventos::detener() {
    seguirCorriendo_ = false;
}
