#include "includes/common/eventos/EventoFactory.h"

#include "includes/common/excepciones/EventoDesconocidoError.h"

std::shared_ptr<Evento> EventoFactory::instanciar(uint32_t uuidRemitente, Protocolo &protocolo) {
  uint16_t UUIDEvento = protocolo.recibirNumUnsigned16();
  switch (UUIDEvento) {

    case UUID_EVENTO_CREAR_PARTIDA:
      return std::make_shared<EventoCrearPartida>(uuidRemitente, protocolo);

    case UUID_EVENTO_UNIRSE_A_PARTIDA:
      return std::make_shared<EventoUnirseAPartida>(uuidRemitente, protocolo);

    case UUID_EVENTO_INICIAR_PARTIDA:
      return std::make_shared<EventoIniciarPartida>(uuidRemitente, protocolo);

    case UUID_EVENTO_DESCONEXION:
      return std::make_shared<EventoDesconexion>(uuidRemitente, protocolo);

    case UUID_EVENTO_ACELERAR:
      return std::make_shared<EventoAcelerar>(uuidRemitente, protocolo);

    case UUID_EVENTO_DESACELERAR:
      return std::make_shared<EventoDesacelerar>(uuidRemitente, protocolo);

    case UUID_EVENTO_FRENAR:
      return std::make_shared<EventoFrenar>(uuidRemitente, protocolo);

    case UUID_EVENTO_DEJAR_DE_FRENAR:
      return std::make_shared<EventoDejarDeFrenar>(uuidRemitente, protocolo);

    case UUID_EVENTO_DOBLAR_IZQUIERDA:
      return std::make_shared<EventoDoblarIzquierda>(uuidRemitente, protocolo);

    case UUID_EVENTO_DEJAR_DE_DOBLAR_IZQUIERDA:
      return std::make_shared<EventoDejarDeDoblarIzquierda>(uuidRemitente, protocolo);

    case UUID_EVENTO_DOBLAR_DERECHA:
      return std::make_shared<EventoDoblarDerecha>(uuidRemitente, protocolo);

    case UUID_EVENTO_DEJAR_DE_DOBLAR_DERECHA:
      return std::make_shared<EventoDejarDeDoblarDerecha>(uuidRemitente, protocolo);

    case UUID_EVENTO_SNAPSHOT:
      return std::make_shared<EventoSnapshot>(uuidRemitente, protocolo);

    case UUID_EVENTO_PARTIDA_INICIADA:
      return std::make_shared<EventoPartidaIniciada>(uuidRemitente, protocolo);

    case UUID_EVENTO_FIN_CARRERA:
      return std::make_shared<EventoFinCarrera>(uuidRemitente, protocolo);

    case UUID_EVENTO_APARECIO_CONSUMIBLE:
      return std::make_shared<EventoAparecioConsumible>(uuidRemitente, protocolo);

    case UUID_EVENTO_BARRO_PISADO:
      return std::make_shared<EventoBarroPisado>(uuidRemitente, protocolo);

    case UUID_EVENTO_CHOQUE:
      return std::make_shared<EventoChoque>(uuidRemitente, protocolo);

    case UUID_EVENTO_DESAPARECIO_CONSUMIBLE:
      return std::make_shared<EventoDesaparecioConsumible>(uuidRemitente, protocolo);

    case UUID_EVENTO_EXPLOSION:
      return std::make_shared<EventoExplosion>(uuidRemitente, protocolo);

    case UUID_EVENTO_FIN_BARRO:
      return std::make_shared<EventoFinBarro>(uuidRemitente, protocolo);

    case UUID_EVENTO_PARTIDA_CREADA:
      return std::make_shared<EventoPartidaCreada>(uuidRemitente, protocolo);

    case UUID_EVENTO_SNAPSHOT_LOBBY:
      return std::make_shared<EventoSnapshotLobby>(uuidRemitente, protocolo);

    case UUID_EVENTO_SNAPSHOT_SALA:
      return std::make_shared<EventoSnapshotSala>(uuidRemitente, protocolo);

    case UUID_EVENTO_UNIRSE_A_SALA:
      return std::make_shared<EventoUnirseASala>(uuidRemitente, protocolo);
    
    case UUID_EVENTO_FRENADA:
      return std::make_shared<EventoFrenada>(uuidRemitente, protocolo);

    default:
      throw EventoDesconocidoError(ERROR_EVENTO_DESCONOCIDO);
  }
}
