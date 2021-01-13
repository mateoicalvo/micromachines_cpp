#ifndef _CONFIG_SERVIDOR_H_
#define _CONFIG_SERVIDOR_H_

#define RUTA_CONFIG_SERVIDOR "config/server_settings.json"

#define CONFIG_SERVIDOR ConfigServidor::instancia()

#include <string>
#include <vector>

#include "includes/3rd-party/jsoncpp/json.hpp"

class ConfigServidor {
private:
    ConfigServidor(const std::string& rutaArchivo);
    Json json_;
    std::vector<int> tilesTierra_;
    std::vector<int> tilesPista_;

public:
    static ConfigServidor& instancia();
    std::string puertoServidor();
    std::string hostServidor();
    unsigned int maxClientesEnEspera();
    unsigned int snapshotsEnviadosPorSegundo();

    float anchoTile();
    
    std::string rutaPistas();
    std::vector<int>& tilesTierra();
    std::vector<int>& tilesPista();
    int tileArena();
    int tileBarro();
    int tileAceite();
    int tileVacio();
    
    uint32_t simulacionesPorSegundo();
    uint32_t iteracionesPosicion();
    uint32_t iteracionesVelocidad();

    unsigned int velocidadMaxVehiculoAdelante();
    unsigned int velocidadMaxVehiculoAtras();
    unsigned int aceleracionVehiculo();
    unsigned int maniobrabilidadVehiculo();
    unsigned int agarreVehiculo();
    unsigned int saludVehiculo();
    float anchoVehiculo();
    float largoVehiculo();

    float ladoSuperficie();

    int cantidadMaximaModificadores();
    int factorAparicionModificador();

    uint8_t disminucionVidaChoqueConVehiculo();
};

#endif
