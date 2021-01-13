#include "includes/servidor/modelo/Mundo.h"

#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <stdlib.h>


#include "includes/servidor/utils/ConfigServidor.h"
#include "includes/3rd-party/jsoncpp/json.hpp"
#include "includes/common/Tile.h"
#include "includes/common/Conversor.h"
#include "includes/servidor/modelo/superficies/SuperficieFactory.h"
#include "includes/servidor/modelo/movimiento/Posicion.h"
#include "includes/servidor/modelo/entidades/CajaVida.h"
#include "includes/servidor/modelo/entidades/Barro.h"
#include "includes/servidor/modelo/entidades/Boost.h"
#include "includes/servidor/modelo/entidades/Aceite.h"
#include "includes/servidor/modelo/entidades/Piedra.h"
#include "includes/common/eventos/EventoSnapshot.h"

//TODO: Crear conversor de coordenadas?
//Forward declaration
static void cargarSuelo(uint16_t largoX, uint16_t largoY, std::map<Tile, std::shared_ptr<Superficie>>& tilesASuelo, std::vector<Tile>& tilesConPista, Json& pistaJson);
static void cargarPosicionesIniciales(uint16_t largoX, uint16_t largoY, std::queue<Posicion>& tiles, Json& pistaJson);

Mundo::Mundo(uint16_t uuidPista) :
    fisicas_(eventosOcurridos_, contactListener_, *this),
    snapshotsEnviadosPorSegundo_(60/CONFIG_SERVIDOR.snapshotsEnviadosPorSegundo()),
    contactListener_(fisicas_),
    carrera_(eventosOcurridos_) {

    for (uint8_t id = 1; id < 255; ++id) {
        uuidsObjetos_.push(id);
    }  
    
    //TODO: Es mejor cargar todas las pistas al inicio y luego hacer un get() para no tener que ir
    // siempre a disco.
    std::string rutaPista = CONFIG_SERVIDOR.rutaPistas() + std::to_string(uuidPista) + ".json";
    std::ifstream archivoPista(rutaPista);
    Json pistaJson;
    archivoPista >> pistaJson;
    uint16_t largoX = pistaJson["dimensiones"]["x"].get<uint16_t>();
    uint16_t largoY = pistaJson["dimensiones"]["y"].get<uint16_t>();

    cargarSuelo(largoX, largoY, tileASuelo_, tilesConPista_, pistaJson);
    cargarPosicionesIniciales(largoX, largoY, posicionesIniciales_, pistaJson);
    carrera_.cargarDesdeJson(pistaJson);
    
    fisicas_.generarSuelo(tileASuelo_);
    fisicas_.generarCheckpoints(carrera_.checkpoints());
    srand(time(NULL));
}

Mundo::~Mundo() {
    //TODO: IMPLEMENTAR
}

void Mundo::step(uint32_t numeroIteracion) {
    fisicas_.step(numeroIteracion);
    for (auto& kv : jugadoresAVehiculos_) {
        kv.second.step();
    }
    //TODO: Chequear por la negativa?
    //FIXME: NO DEBIERA ESTAR LIGADO AL STEP DEL MUNDO, PERO MUNDO TENDRÍA QUE SER MONITOR
    if((numeroIteracion % snapshotsEnviadosPorSegundo_) == 0) {
        std::map<uint8_t, datosVehiculo_> idsADatosVehiculo = serializarEstado();
        std::shared_ptr<Evento> snapshot = std::make_shared<EventoSnapshot>(std::move(idsADatosVehiculo));
        eventosOcurridos_.put(snapshot);
    }
    agregarModificadores(numeroIteracion);
}

Cola<std::shared_ptr<Evento>>& Mundo::eventosOcurridos() {
    return eventosOcurridos_;
}

void Mundo::recuperarUuid(uint8_t uuid) {
    uuidsObjetos_.push(uuid);
}

uint8_t Mundo::agregarVehiculo(std::shared_ptr<Jugador> unJugador) {
    //TODO: En cual de los casilleros?
    //FIXME: Nada impide top() de pila vacia si hay mas jugadores
    Posicion posicion = posicionesIniciales_.front();
    posicion.x_ = Conversor::tileAMetro(posicion.x_);
    posicion.y_ = Conversor::tileAMetro(posicion.y_);
    uint8_t uuid = uuidsObjetos_.front();
    jugadoresAVehiculos_.emplace(unJugador->uuid(), Vehiculo(uuid,
            CONFIG_SERVIDOR.velocidadMaxVehiculoAdelante(),
            CONFIG_SERVIDOR.velocidadMaxVehiculoAtras(),
            CONFIG_SERVIDOR.aceleracionVehiculo(),
            CONFIG_SERVIDOR.maniobrabilidadVehiculo(),
            CONFIG_SERVIDOR.agarreVehiculo(),
            CONFIG_SERVIDOR.saludVehiculo(),
            posicion,
            unJugador));
            
    jugadoresAIDVehiculo_[unJugador->uuid()] = uuid;
    fisicas_.agregarVehiculo(jugadoresAVehiculos_.at(unJugador->uuid()), posicion);
    posicionesIniciales_.pop();

    carrera_.registrarVehiculo(jugadoresAVehiculos_.at(unJugador->uuid()));

    uuidsObjetos_.pop();
    return uuid;
}

std::map<uint8_t, datosVehiculo_> Mundo::getEstadoInicial() {
    //FIXME No devuelve el estado inicial en llamadas sucesivas
    return serializarEstado();
}

void Mundo::agregarModificadores(uint32_t nroIteracion) {
    if (nroIteracion % CONFIG_SERVIDOR.factorAparicionModificador() != 0) {
        return;
    }
    //SORTEAR EL QUE VA A APARECER
    if (uuidsObjetos_.size() == 0) {
        return;
    }
    int tile = rand() % tilesConPista_.size();
    Tile& destino = tilesConPista_[tile];
    Posicion posicion(Conversor::tileAMetro(destino.x_) + 0.5f*CONFIG_SERVIDOR.anchoTile(),
        Conversor::tileAMetro(destino.y_) + 0.5f*CONFIG_SERVIDOR.anchoTile(), 0);
    uint8_t uuid = uuidsObjetos_.front();
    
    int modificador = rand() % 5 + 1;
    //TODO: REFACTOIRZAR ESTE HORROR
    if (modificador == UUID_VIDA) {
        //TODO: AL CONFIG SERVIDOR LOS 20 DE VIDA
        modificadores_.emplace(uuid, std::make_shared<CajaVida>(uuid, 20));
        fisicas_.agregarModificador(modificadores_.at(uuid), UUID_VIDA, posicion);
    } else if (modificador == UUID_BARRO) {
        modificadores_.emplace(uuid, std::make_shared<Barro>(uuid));
        fisicas_.agregarModificador(modificadores_.at(uuid), UUID_BARRO, posicion);
    } else if (modificador == UUID_PIEDRA) {
        modificadores_.emplace(uuid, std::make_shared<Piedra>(uuid));
        fisicas_.agregarModificador(modificadores_.at(uuid), UUID_PIEDRA, posicion);
    } else if (modificador == UUID_ACEITE) {
        modificadores_.emplace(uuid, std::make_shared<Aceite>(uuid));
        fisicas_.agregarModificador(modificadores_.at(uuid), UUID_ACEITE, posicion);
    } else if (modificador == UUID_BOOST) {
        modificadores_.emplace(uuid, std::make_shared<Boost>(uuid));
        fisicas_.agregarModificador(modificadores_.at(uuid), UUID_BOOST, posicion);
    }
    uuidsObjetos_.pop();
}

void Mundo::manejar(Evento& e) {
    e.actualizar(*this);
}

void Mundo::manejar(EventoAcelerar& e) {
    uint32_t jugador = e.uuidRemitente();
    fisicas_.acelerar(jugadoresAIDVehiculo_[jugador]);
}

void Mundo::manejar(EventoDesacelerar& e) {
    uint32_t jugador = e.uuidRemitente();
    fisicas_.desacelerar(jugadoresAIDVehiculo_[jugador]);
}

void Mundo::manejar(EventoFrenar& e) {
    uint32_t jugador = e.uuidRemitente();
    fisicas_.frenar(jugadoresAIDVehiculo_[jugador]);
    Posicion p = fisicas_.getPosicionDe(jugadoresAIDVehiculo_.at(e.uuidRemitente()));
    std::shared_ptr<Evento> frenada = std::make_shared<EventoFrenada>(p.x_, p.y_);
    eventosOcurridos_.put(frenada);
}

void Mundo::manejar(EventoDejarDeFrenar& e) {
    uint32_t jugador = e.uuidRemitente();
    fisicas_.dejarDeFrenar(jugadoresAIDVehiculo_[jugador]);
}

void Mundo::manejar(EventoDoblarIzquierda& e) {
    uint32_t jugador = e.uuidRemitente();
    fisicas_.doblarIzquierda(jugadoresAIDVehiculo_[jugador]);
}

void Mundo::manejar(EventoDejarDeDoblarIzquierda& e) {
    uint32_t jugador = e.uuidRemitente();
    fisicas_.dejarDeDoblarIzquierda(jugadoresAIDVehiculo_[jugador]);
}

void Mundo::manejar(EventoDoblarDerecha& e) {
    uint32_t jugador = e.uuidRemitente();
    fisicas_.doblarDerecha(jugadoresAIDVehiculo_[jugador]);
}

void Mundo::manejar(EventoDejarDeDoblarDerecha& e) {
    uint32_t jugador = e.uuidRemitente();
    fisicas_.dejarDeDoblarDerecha(jugadoresAIDVehiculo_[jugador]);
}

//FIXME: No hardcodear
// El sistema de referencia de la pista está arriba a la izquierda,
// mientras que en el servidor está abajo a la derecha.
static void cargarSuelo(uint16_t largoX, uint16_t largoY, std::map<Tile, std::shared_ptr<Superficie>>& tilesASuelo, std::vector<Tile>& tilesConPista, Json& pistaJson) {
    for (int i = 0; i < largoX; ++i) {
        for (int j = 0; j < largoY; ++j) {
            int uuidTerreno = pistaJson["capas"]["terreno"][std::to_string(i)][std::to_string(j)].get<int>();
            int uuidPista = pistaJson["capas"]["pista"][std::to_string(i)][std::to_string(j)].get<int>();
            // Hay pista
            if (uuidPista != CONFIG_SERVIDOR.tileVacio()) {
                tilesASuelo[Tile(i, largoY - j - 1)] = SuperficieFactory::instanciar(uuidPista);
                tilesConPista.emplace_back(Tile(i, largoY - j - 1));
                
            } else {
                tilesASuelo[Tile(i, largoY - j - 1)] = SuperficieFactory::instanciar(uuidTerreno);
            }
        }
    }
}

static void cargarPosicionesIniciales(uint16_t largoX, uint16_t largoY, std::queue<Posicion>& tiles_, Json& pistaJson) {
    int cupos = pistaJson["posicionesIniciales"]["cantidad"].get<int>();
    for (int i = 0; i < cupos; ++i) {
        float x = pistaJson["posicionesIniciales"][std::to_string(i)]["x"].get<float>();
        float y = largoY - pistaJson["posicionesIniciales"][std::to_string(i)]["y"].get<float>();
        tiles_.emplace(Posicion(x, y, 0.0f));
    }
}

std::map<uint8_t, datosVehiculo_> Mundo::serializarEstado() {
    std::map<uint8_t, datosVehiculo_> idsADatosVehiculo;
    for (const auto& kv : jugadoresAIDVehiculo_) {
        uint8_t idVehiculo = jugadoresAIDVehiculo_.at(kv.first);
        //FISICAS DE FISICAS
        Posicion posicion = fisicas_.getPosicionDe(idVehiculo);
        //LOGICA DE MUNDO(YO)
        uint8_t salud = jugadoresAVehiculos_.at(kv.first).salud();
        //FIXME: No debiera ser así
        uint8_t visible = 1;
        idsADatosVehiculo.emplace(idVehiculo, datosVehiculo_{
            posicion.x_,
            posicion.y_,
            posicion.anguloDeg_,
            salud,
            visible
        });
    }
    return idsADatosVehiculo;
}
