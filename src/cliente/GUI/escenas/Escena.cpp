#include "includes/cliente/GUI/escenas/Escena.h"

Escena::Escena(std::stack<std::shared_ptr<Escena>> &escenas,
               Renderizador &renderizador,
               ColaBloqueante<std::shared_ptr<Evento>> &eventosAEnviar_,
               Sonido &musicaAmbiente) :
    escenas_(escenas),
    renderizador_(renderizador),
    eventosAEnviar_(eventosAEnviar_),
    musicaAmbiente(musicaAmbiente) {}

Escena::~Escena() {

}
