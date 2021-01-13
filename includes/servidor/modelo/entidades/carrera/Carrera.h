#ifndef _CARRERA_H_
#define _CARRERA_H_

#include <map>
#include <vector>

#include "includes/3rd-party/jsoncpp/json.hpp"
#include "includes/servidor/modelo/entidades/carrera/Checkpoint.h"
#include "includes/common/ColaProtegida.h"
#include "includes/common/eventos/Evento.h"

#define ID_META 0

//Forward declarations
class Vehiculo;

class Carrera {
private:
    std::map<int, Checkpoint> checkpoints_;
    std::map<uint8_t, int> idsVehiculosAidsCheckpoints_;
    std::map<uint8_t, int> idsVehiculosAVueltas_;
    int numeroDeVueltas_;
    std::vector<uint8_t> podio_;
    ColaProtegida<std::shared_ptr<Evento>>& eventosMundo_;
    
    bool finalizada();

public:
    Carrera(ColaProtegida<std::shared_ptr<Evento>>& eventosMundo);
    void cargarDesdeJson(Json& pistaJson);
    std::map<int, Checkpoint>& checkpoints();
    Checkpoint& ultimoCheckpointDe(Vehiculo& vehiculo);
    void setCheckpoint(Vehiculo& vehiculo, Checkpoint& checkpoint);
    void registrarVehiculo(Vehiculo& vehiculo);
};

#endif
