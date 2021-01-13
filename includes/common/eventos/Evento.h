#ifndef _EVENTO_H_
#define _EVENTO_H_

#include "includes/common/red/Protocolo.h"

//Forward declarations
class Handler;

#define UUID_EVENTO_ACELERAR                    1
#define UUID_EVENTO_DESACELERAR                 2
#define UUID_EVENTO_FRENAR                      3
#define UUID_EVENTO_DEJAR_DE_FRENAR             4
#define UUID_EVENTO_DOBLAR_IZQUIERDA            5
#define UUID_EVENTO_DEJAR_DE_DOBLAR_IZQUIERDA   6
#define UUID_EVENTO_DOBLAR_DERECHA              7
#define UUID_EVENTO_DEJAR_DE_DOBLAR_DERECHA     8

#define UUID_EVENTO_CREAR_PARTIDA               9
#define UUID_EVENTO_PARTIDA_AGREGADA            10
#define UUID_EVENTO_UNIRSE_A_PARTIDA            11
#define UUID_EVENTO_INICIAR_PARTIDA             12
#define UUID_EVENTO_DESCONEXION                 13
#define UUID_EVENTO_PARTIDA_INICIADA            14
#define UUID_EVENTO_SNAPSHOT                    15
#define UUID_EVENTO_FIN_CARRERA                 16
#define UUID_EVENTO_APARECIO_CONSUMIBLE         17
#define UUID_EVENTO_BARRO_PISADO                18
#define UUID_EVENTO_CHOQUE                      19
#define UUID_EVENTO_DESAPARECIO_CONSUMIBLE      20
#define UUID_EVENTO_EXPLOSION                   21
#define UUID_EVENTO_FIN_BARRO                   22
#define UUID_EVENTO_PARTIDA_CREADA              23
#define UUID_EVENTO_SNAPSHOT_LOBBY              24
#define UUID_EVENTO_SNAPSHOT_SALA               25
#define UUID_EVENTO_UNIRSE_A_SALA               26
#define UUID_EVENTO_FRENADA                     27


// TODO: Crear constructor por movimiento
//TODO: Setear id en cada evento creado
// TODO: implementar envio y construccion
// TODO: achicar para que el envio sea mas eficiente según el máximo de eventos
class Evento {
private:
    uint32_t UUIDRemitente_;
protected:
    uint16_t UUIDEvento_;
public:
    Evento(uint32_t uuidRemitente);
    virtual ~Evento() {}
    virtual void enviarse(Protocolo& protocolo) = 0;
    virtual void actualizar(Handler& handler) = 0;
    uint32_t uuidRemitente();
    void setRemitente(uint32_t uuidRemitente);
};

#endif
