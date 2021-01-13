#include "includes/servidor/modelo/fisicas/transformaciones/Quitar.h"

#include "includes/servidor/modelo/fisicas/Fisicas.h"
#include "includes/3rd-party/Box2D/Box2D.h"
#include "includes/common/eventos/EventoDesaparecioConsumible.h"

Quitar::Quitar(Fisicas& fisicas, b2Body* cuerpo, uint8_t uuidCuerpo) :
    Transformacion(fisicas),
    cuerpo_(cuerpo),
    uuidCuerpo_(uuidCuerpo) {
}

void Quitar::aplicar() {
    cuerpo_->GetWorld()->DestroyBody(cuerpo_);
    std::shared_ptr<Evento> desaparicion = std::make_shared<EventoDesaparecioConsumible>(uuidCuerpo_);
    fisicas_.ocurrio(desaparicion);
    fisicas_.nuevoUuidDisponible(uuidCuerpo_);
}
