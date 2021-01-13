#include "includes/servidor/modelo/fisicas/Fisicas.h"

#include "includes/servidor/utils/ConfigServidor.h"
#include "includes/servidor/modelo/Mundo.h"

#include "includes/servidor/modelo/entidades/Vehiculo.h"
#include "includes/servidor/modelo/entidades/CajaVida.h"
#include "includes/servidor/modelo/entidades/Barro.h"
#include "includes/servidor/modelo/entidades/Boost.h"
#include "includes/servidor/modelo/entidades/Aceite.h"
#include "includes/servidor/modelo/entidades/Piedra.h"
#include "includes/servidor/modelo/fisicas/transformaciones/Reubicar.h"
#include "includes/servidor/modelo/fisicas/transformaciones/Quitar.h"

#include "includes/common/eventos/EventoAparecioConsumible.h"


//TODO: Fisicas debe conocer de eventos ocurridos?
//Tiene pinta de que no. Por ende tampoco de snapshots por segundo
Fisicas::Fisicas(Cola<std::shared_ptr<Evento>>& eventosOcurridos, ContactListener& contactListener, Mundo& mundo) :
    gravedad_(0, 0),
    mundoBox2D_(std::make_shared<b2World>(gravedad_)),
    frecuencia_((double)1 / (double)CONFIG_SERVIDOR.simulacionesPorSegundo()),
    iteracion_(0),
    eventosOcurridos_(eventosOcurridos),
    mundo_(mundo) {
    
    mundoBox2D_->SetContactListener(&contactListener);
}

Fisicas::~Fisicas() {
}

void Fisicas::ocurrio(std::shared_ptr<Evento> unEvento) {
    eventosOcurridos_.put(unEvento);
}

void Fisicas::agregarModificador(std::shared_ptr<Modificador> modificador, uint8_t tipo, Posicion& posicion) {
    float ladoModificador = 5.0f;//CONFIG_SEVIDOR.ladoModificador();
    b2BodyDef bodyDef;
    bodyDef.userData = modificador.get();
    float x = posicion.x_; 
    float y = posicion.y_;
    bodyDef.position.Set(x, y);

    b2Body* cuerpo = mundoBox2D_->CreateBody(&bodyDef);
    b2PolygonShape forma;        
    forma.SetAsBox(ladoModificador/2.0f, ladoModificador/2.0f);
	b2FixtureDef caracteristicas;
	caracteristicas.shape = &forma;
    caracteristicas.isSensor = true;
	cuerpo->CreateFixture(&caracteristicas);
    colisionables_[modificador->uuid()] = cuerpo;
    std::shared_ptr<Evento> aparicion = std::make_shared<EventoAparecioConsumible>(modificador->uuid(), tipo, x, y);
    eventosOcurridos_.put(aparicion);
}

void Fisicas::generarSuelo(std::map<Tile, std::shared_ptr<Superficie>>& tileASuelo) {
    //TODO: Implementar: es arena tierra y pista.
    float anchoTile = CONFIG_SERVIDOR.anchoTile();
    for (const auto& kv : tileASuelo) {
        b2BodyDef bodyDef;
        bodyDef.userData = kv.second.get();        
        
        float x = anchoTile*(float)kv.first.x_ + 0.5f*anchoTile; 
        float y = anchoTile*(float)kv.first.y_ + 0.5f*anchoTile;
	    bodyDef.position.Set(x, y);
        
        b2Body* cuerpo = mundoBox2D_->CreateBody(&bodyDef);
        b2PolygonShape forma;        
        forma.SetAsBox(CONFIG_SERVIDOR.ladoSuperficie()/2.0f, CONFIG_SERVIDOR.ladoSuperficie()/2.0f);
	    b2FixtureDef caracteristicas;
	    caracteristicas.shape = &forma;
        caracteristicas.isSensor = true;
	    cuerpo->CreateFixture(&caracteristicas);
    }
}

/*void Fisicas::generarSuperficies(std::map<Tile, std::shared_ptr<Superficie>>& tileASuperficie) {
    //TODO: Implementar
}*/

void Fisicas::generarCheckpoints(std::map<int, Checkpoint>& checkpoints) {
    for (auto& kv : checkpoints) {
        b2BodyDef bodyDef;
        //https://stackoverflow.com/questions/5377434/does-stdmapiterator-return-a-copy-of-value-or-a-value-itself
        bodyDef.userData = &kv.second;
                
        float ancho = kv.second.ancho();
        float largo = kv.second.alto();

        float x = kv.second.posicion().x_;
        float y = kv.second.posicion().y_;

        bodyDef.position.Set(x, y);
        
        b2Body* cuerpo = mundoBox2D_->CreateBody(&bodyDef);
        b2PolygonShape forma;        
        forma.SetAsBox(ancho/2.0f, largo/2.0f);
	    b2FixtureDef caracteristicas;
	    caracteristicas.shape = &forma;
        caracteristicas.isSensor = true;
	    cuerpo->CreateFixture(&caracteristicas);
    }
}
void Fisicas::acelerar(uint8_t uuidVehiculo) {
    vehiculos_.at(uuidVehiculo)->acelerando();
}

void Fisicas::desacelerar(uint8_t uuidVehiculo) {
    vehiculos_.at(uuidVehiculo)->desacelerando();
}

void Fisicas::frenar(uint8_t uuidVehiculo) {
    vehiculos_.at(uuidVehiculo)->frenando();
}

void Fisicas::dejarDeFrenar(uint8_t uuidVehiculo) {
    vehiculos_.at(uuidVehiculo)->dejandoDeFrenar();
}

void Fisicas::doblarIzquierda(uint8_t uuidVehiculo) {
    vehiculos_.at(uuidVehiculo)->doblandoIzquierda();
}

void Fisicas::dejarDeDoblarIzquierda(uint8_t uuidVehiculo) {
    vehiculos_.at(uuidVehiculo)->dejandoDeDoblarIzquierda();
}

void Fisicas::doblarDerecha(uint8_t uuidVehiculo) {
    vehiculos_.at(uuidVehiculo)->doblandoDerecha();
}

void Fisicas::dejarDeDoblarDerecha(uint8_t uuidVehiculo) {
    vehiculos_.at(uuidVehiculo)->dejandoDeDoblarDerecha();
}

void Fisicas::agregarVehiculo(Vehiculo& vehiculo, Posicion& posicion) {
    vehiculos_.emplace(vehiculo.uuid(), std::make_shared<B2DVehiculo>(mundoBox2D_.get(), vehiculo));
    b2Vec2 posicionBox2D = {posicion.x_, posicion.y_};
    vehiculos_.at(vehiculo.uuid())->getB2D()->SetTransform(posicionBox2D, (float)posicion.anguloDeg_);
}

Posicion Fisicas::getPosicionDe(uint8_t idCuerpo) {
    
    b2Body* cuerpoFisico = vehiculos_.at(idCuerpo)->getB2D();
    b2Vec2 posicion = cuerpoFisico->GetPosition();
    float32 angulo = cuerpoFisico->GetAngle();
    int anguloDeg = (int)(angulo*RADTODEG) % 360;
    anguloDeg *= -1;
    if (anguloDeg < 0) {
        anguloDeg += 360;
    }
    return Posicion(posicion.x, posicion.y, anguloDeg);
}

void Fisicas::nuevoUuidDisponible(uint8_t uuid) {
    mundo_.recuperarUuid(uuid);
}

void Fisicas::step(uint32_t numeroIteracion) {
    //TODO: Todos haran step
    //Acá se alteran los cuerpos físicos.
    for (const auto& kv : vehiculos_) {
        kv.second->step();
    }
    uint32_t escala = numeroIteracion - iteracion_;
    float tiempoAtranscurrir = (float)escala * frecuencia_;
    mundoBox2D_->Step(tiempoAtranscurrir, CONFIG_SERVIDOR.iteracionesVelocidad(), CONFIG_SERVIDOR.iteracionesPosicion());
    iteracion_ = numeroIteracion;
    //TODO: Aplicar transformaciones y encolar eventos pertinentes.
    while(!transformaciones_.empty()) {
        std::shared_ptr<Transformacion> t = transformaciones_.front();
        t->aplicar();
        transformaciones_.pop();
    }
}

//TODO: REFACTORIZAR, TODOS HACEN LO MISMO
void Fisicas::reubicar(Vehiculo& vehiculo, Posicion& posicion) {
    b2Body* cuerpoVehiculo = vehiculos_.at(vehiculo.uuid())->getB2D();
    std::shared_ptr<Transformacion> t = std::make_shared<Reubicar>(*this, cuerpoVehiculo, posicion);
    transformaciones_.push(t);
}

void Fisicas::quitar(Barro& barro) {
    b2Body* cuerpo = colisionables_.at(barro.uuid());
    std::shared_ptr<Transformacion> t = std::make_shared<Quitar>(*this, cuerpo, barro.uuid());
    transformaciones_.push(t);
}

void Fisicas::quitar(Boost& boost) {
    b2Body* cuerpo = colisionables_.at(boost.uuid());
    std::shared_ptr<Transformacion> t = std::make_shared<Quitar>(*this, cuerpo, boost.uuid());
    transformaciones_.push(t);
}

void Fisicas::quitar(Aceite& aceite) {
    b2Body* cuerpo = colisionables_.at(aceite.uuid());
    std::shared_ptr<Transformacion> t = std::make_shared<Quitar>(*this, cuerpo, aceite.uuid());
    transformaciones_.push(t);
}

void Fisicas::quitar(Piedra& piedra) {
    b2Body* cuerpo = colisionables_.at(piedra.uuid());
    std::shared_ptr<Transformacion> t = std::make_shared<Quitar>(*this, cuerpo, piedra.uuid());
    transformaciones_.push(t);
}

void Fisicas::quitar(CajaVida& cajaVida) {
    b2Body* cuerpo = colisionables_.at(cajaVida.uuid());
    std::shared_ptr<Transformacion> t = std::make_shared<Quitar>(*this, cuerpo, cajaVida.uuid());
    transformaciones_.push(t);
}
