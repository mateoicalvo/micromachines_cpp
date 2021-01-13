#include "includes/servidor/utils/ConfigServidor.h"

#include <fstream>

ConfigServidor& ConfigServidor::instancia() {
    static ConfigServidor config_(RUTA_CONFIG_SERVIDOR);
    return config_;
}

ConfigServidor::ConfigServidor(const std::string& rutaArchivo) {
    std::ifstream archivo(rutaArchivo);
    archivo >> json_;
    tilesTierra_ = json_["tiles"]["tilesTierra"].get<std::vector<int>>();
    tilesPista_ = json_["tiles"]["tilesPista"].get<std::vector<int>>();
}

std::string ConfigServidor::hostServidor() {
    return json_["red"]["host"].get<std::string>();
}

std::string ConfigServidor::puertoServidor() {
    return json_["red"]["puerto"].get<std::string>();
}

unsigned int ConfigServidor::maxClientesEnEspera() {
    return json_["red"]["maxClientesEnEspera"].get<unsigned int>();
}

unsigned int ConfigServidor::snapshotsEnviadosPorSegundo() {
    return json_["red"]["snapshotsEnviadosPorSegundo"].get<unsigned int>();
}

std::string ConfigServidor::rutaPistas() {
    return json_["rutaPistas"].get<std::string>();
}

std::vector<int>& ConfigServidor::tilesTierra() {
    return tilesTierra_;
}

std::vector<int>& ConfigServidor::tilesPista() {
    return tilesPista_;
}

int ConfigServidor::tileArena() {
    return json_["tiles"]["arena"].get<int>();
}

int ConfigServidor::tileBarro() {
    return json_["tiles"]["barro"].get<int>();
}

int ConfigServidor::tileAceite() {
    return json_["tiles"]["aceite"].get<int>();
}

int ConfigServidor::tileVacio() {
    return json_["tiles"]["vacio"].get<int>();
}

uint32_t ConfigServidor::simulacionesPorSegundo() {
    return json_["fisicas"]["simulacionesPorSegundo"].get<uint32_t>();
}

uint32_t ConfigServidor::iteracionesPosicion() {
    return json_["fisicas"]["iteracionesPosicion"].get<uint32_t>();
}

uint32_t ConfigServidor::iteracionesVelocidad() {
    return json_["fisicas"]["iteracionesVelocidad"].get<uint32_t>();
}

unsigned int ConfigServidor::velocidadMaxVehiculoAdelante() {
    return json_["modelo"]["vehiculo"]["velocidadMaxAdelante"].get<unsigned int>();
}
unsigned int ConfigServidor::velocidadMaxVehiculoAtras() {
    return json_["modelo"]["vehiculo"]["velocidadMaxAtras"].get<unsigned int>();
}
unsigned int ConfigServidor::aceleracionVehiculo() {
    return json_["modelo"]["vehiculo"]["aceleracionVehiculo"].get<unsigned int>();
}
unsigned int ConfigServidor::maniobrabilidadVehiculo() {
    return json_["modelo"]["vehiculo"]["maniobrabilidadVehiculo"].get<unsigned int>();
}
unsigned int ConfigServidor::agarreVehiculo() {
    return json_["modelo"]["vehiculo"]["agarreVehiculo"].get<unsigned int>();
}
unsigned int ConfigServidor::saludVehiculo() {
    return json_["modelo"]["vehiculo"]["saludVehiculo"].get<unsigned int>();
}

float ConfigServidor::anchoVehiculo() {
    return json_["modelo"]["vehiculo"]["ancho"].get<float>();
}

float ConfigServidor::largoVehiculo() {
    return json_["modelo"]["vehiculo"]["largo"].get<float>();
}

float ConfigServidor::ladoSuperficie() {
    return json_["modelo"]["superficies"]["lado"].get<float>();
}

float ConfigServidor::anchoTile() {
    return json_["modelo"]["anchoTile"].get<float>();
}

uint8_t ConfigServidor::disminucionVidaChoqueConVehiculo() {
    return json_["modelo"]["disminucionVida"]["vsVehiculo"].get<uint8_t>();
}

int ConfigServidor::cantidadMaximaModificadores() {
    return json_["modelo"]["modificadores"]["cantidadMaxima"].get<int>();
}

int ConfigServidor::factorAparicionModificador() {
    return json_["modelo"]["modificadores"]["factorAparicion"].get<int>();
}
