#include "includes/servidor/modelo/entidades/carrera/Carrera.h"

#include "includes/servidor/modelo/entidades/Vehiculo.h"
#include "includes/common/Conversor.h"
#include "includes/common/eventos/EventoFinCarrera.h"

Carrera::Carrera(ColaProtegida<std::shared_ptr<Evento>>& eventosMundo) :
    numeroDeVueltas_(0),
    eventosMundo_(eventosMundo) {
}

void Carrera::cargarDesdeJson(Json& pistaJson) {
    int cantidadCheckpoints = pistaJson["checkpoints"]["cantidad"].get<int>();
    uint16_t largoY = pistaJson["dimensiones"]["y"].get<uint16_t>();
        
    //TODO: Cargo checkpoints, meta es aparte (?) ¿Lo es?
    for (int i = 0; i < cantidadCheckpoints; ++i) {
        float x = pistaJson["checkpoints"][std::to_string(i)]["x"].get<float>();
        float y = largoY - pistaJson["checkpoints"][std::to_string(i)]["y"].get<float>();
        float ancho = pistaJson["checkpoints"][std::to_string(i)]["ancho"].get<float>();
        float largo = pistaJson["checkpoints"][std::to_string(i)]["largo"].get<float>();
        uint16_t angulo = pistaJson["checkpoints"][std::to_string(i)]["anguloRespawn"].get<uint16_t>();
        Posicion posicion(Conversor::tileAMetro(x), Conversor::tileAMetro(y), angulo);
        checkpoints_.emplace(i, Checkpoint(*this, i, (i+1) % cantidadCheckpoints, ancho, largo, posicion));
    }
    numeroDeVueltas_ = pistaJson["vueltas"].get<int>();
}

std::map<int, Checkpoint>& Carrera::checkpoints() {
    return checkpoints_;
}

Checkpoint& Carrera::ultimoCheckpointDe(Vehiculo& vehiculo) {
    return checkpoints_.at(idsVehiculosAidsCheckpoints_.at(vehiculo.uuid()));
}

void Carrera::setCheckpoint(Vehiculo& vehiculo, Checkpoint& checkpoint) {
    idsVehiculosAidsCheckpoints_[vehiculo.uuid()] = checkpoint.id();
    if (checkpoint.id() == ID_META) {
        idsVehiculosAVueltas_[vehiculo.uuid()]++;
        if (idsVehiculosAVueltas_[vehiculo.uuid()] == numeroDeVueltas_) {
            podio_.emplace_back(vehiculo.uuid());
        }
    }
    bool termino = finalizada();
    if (termino) {
        std::shared_ptr<Evento> fin = std::make_shared<EventoFinCarrera>(std::move(podio_));
        eventosMundo_.put(fin);
    }
}

void Carrera::registrarVehiculo(Vehiculo& vehiculo) {
    idsVehiculosAidsCheckpoints_[vehiculo.uuid()] = 0;
    idsVehiculosAVueltas_[vehiculo.uuid()] = 0;
}

bool Carrera::finalizada() {
    for (auto& kv : idsVehiculosAVueltas_) {
        if (kv.second < numeroDeVueltas_) {
            return false;
        }
    }
    return true;
}
