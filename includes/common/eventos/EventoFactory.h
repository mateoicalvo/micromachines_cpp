#ifndef _EVENTO_FACTORY_H_
#define _EVENTO_FACTORY_H_

#include <memory>

#include "includes/common/red/Protocolo.h"
#include "includes/common/eventos/Evento.h"
#include "includes/common/eventos/EventoPartidaIniciada.h"
#include "includes/common/eventos/EventoCrearPartida.h"
#include "includes/common/eventos/EventoUnirseAPartida.h"
#include "includes/common/eventos/EventoIniciarPartida.h"
#include "includes/common/eventos/EventoDesconexion.h"
#include "includes/common/eventos/EventoAcelerar.h"
#include "includes/common/eventos/EventoDesacelerar.h"
#include "includes/common/eventos/EventoFrenar.h"
#include "includes/common/eventos/EventoDejarDeFrenar.h"
#include "includes/common/eventos/EventoDoblarIzquierda.h"
#include "includes/common/eventos/EventoDejarDeDoblarIzquierda.h"
#include "includes/common/eventos/EventoDoblarDerecha.h"
#include "includes/common/eventos/EventoDejarDeDoblarDerecha.h"
#include "includes/common/eventos/EventoSnapshot.h"
#include "includes/common/eventos/EventoFinCarrera.h"
#include "includes/common/eventos/EventoAparecioConsumible.h"
#include "includes/common/eventos/EventoDesaparecioConsumible.h"
#include "includes/common/eventos/EventoChoque.h"
#include "includes/common/eventos/EventoBarroPisado.h"
#include "includes/common/eventos/EventoExplosion.h"
#include "includes/common/eventos/EventoFinBarro.h"
#include "includes/common/eventos/EventoPartidaCreada.h"
#include "includes/common/eventos/EventoSnapshotLobby.h"
#include "includes/common/eventos/EventoSnapshotSala.h"
#include "includes/common/eventos/EventoUnirseASala.h"
#include "includes/common/eventos/EventoFrenada.h"

#define ERROR_EVENTO_DESCONOCIDO "Error al instanciar evento, se utilizó un UUID desconocido."

class EventoFactory {
private:
public:
    static std::shared_ptr<Evento> instanciar(uint32_t uuidRemitente, Protocolo& protocolo);
};

#endif
