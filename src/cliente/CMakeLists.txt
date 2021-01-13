cmake_minimum_required(VERSION 3.10.2)

project(ClienteCMake)

set(SOURCES
        ${PROJECT_SOURCE_DIR}/utils/ConfigCliente.cpp
        ${PROJECT_SOURCE_DIR}/red/SocketTCPCliente.cpp
        ${PROJECT_SOURCE_DIR}/excepciones/SDLException.cpp

        ${PROJECT_SOURCE_DIR}/Cliente.cpp
        ${PROJECT_SOURCE_DIR}/GUI/HiloDibujador.cpp
        ${PROJECT_SOURCE_DIR}/GUI/eventos/EventoGUIClick.cpp
        ${PROJECT_SOURCE_DIR}/GUI/eventos/EventoGUIKeyDown.cpp
        ${PROJECT_SOURCE_DIR}/GUI/eventos/EventoGUIKeyUp.cpp
        ${PROJECT_SOURCE_DIR}/GUI/Camara.cpp
        ${PROJECT_SOURCE_DIR}/GUI/Area.cpp
        ${PROJECT_SOURCE_DIR}/GUI/Renderizador.cpp
        ${PROJECT_SOURCE_DIR}/GUI/Textura.cpp
        ${PROJECT_SOURCE_DIR}/GUI/Texto.cpp
        ${PROJECT_SOURCE_DIR}/GUI/Boton.cpp
        ${PROJECT_SOURCE_DIR}/GUI/Sonido.cpp
        ${PROJECT_SOURCE_DIR}/GUI/Animacion.cpp
        ${PROJECT_SOURCE_DIR}/GUI/AnimacionFactory.cpp
        ${PROJECT_SOURCE_DIR}/GUI/Pista.cpp
        ${PROJECT_SOURCE_DIR}/GUI/Camara.cpp
        ${PROJECT_SOURCE_DIR}/GUI/Ventana.cpp
        ${PROJECT_SOURCE_DIR}/GUI/ObjetoDinamico.cpp
        ${PROJECT_SOURCE_DIR}/GUI/escenas/Escena.cpp
        ${PROJECT_SOURCE_DIR}/GUI/escenas/EscenaMenu.cpp
        ${PROJECT_SOURCE_DIR}/GUI/escenas/EscenaSala.cpp
        ${PROJECT_SOURCE_DIR}/GUI/escenas/EscenaPartida.cpp
        ${PROJECT_SOURCE_DIR}/GUI/escenas/EscenaLobby.cpp
        ${PROJECT_SOURCE_DIR}/GUI/escenas/EscenaPodio.cpp

        ${PROJECT_SOURCE_DIR}/grabador/HiloGrabador.cpp
        ${PROJECT_SOURCE_DIR}/grabador/ffmpeg/codec.cpp
        ${PROJECT_SOURCE_DIR}/grabador/ffmpeg/frame.cpp
        ${PROJECT_SOURCE_DIR}/grabador/ffmpeg/output_format.cpp
        ${PROJECT_SOURCE_DIR}/grabador/ffmpeg/output_stream.cpp
        ${PROJECT_SOURCE_DIR}/grabador/ffmpeg/output_video.cpp
        ${PROJECT_SOURCE_DIR}/grabador/ffmpeg/video_codec.cpp

        ${PROJECT_SOURCE_DIR}/jugadores/Jugador.cpp
        ${PROJECT_SOURCE_DIR}/jugadores/Computadora.cpp


        ${CMAKE_SOURCE_DIR}/src/common/Cronometro.cpp
        ${CMAKE_SOURCE_DIR}/src/common/Hilo.cpp
        ${CMAKE_SOURCE_DIR}/src/common/Handler.cpp
        ${CMAKE_SOURCE_DIR}/src/common/RecibidorEventos.cpp
        ${CMAKE_SOURCE_DIR}/src/common/Conversor.cpp
        ${CMAKE_SOURCE_DIR}/src/common/EnviadorEventos.cpp
        ${CMAKE_SOURCE_DIR}/src/common/eventos/Evento.cpp
        ${CMAKE_SOURCE_DIR}/src/common/eventos/EventoPartidaIniciada.cpp
        ${CMAKE_SOURCE_DIR}/src/common/eventos/EventoCrearPartida.cpp
        ${CMAKE_SOURCE_DIR}/src/common/eventos/EventoUnirseAPartida.cpp
        ${CMAKE_SOURCE_DIR}/src/common/eventos/EventoIniciarPartida.cpp
        ${CMAKE_SOURCE_DIR}/src/common/eventos/EventoDesconexion.cpp
        ${CMAKE_SOURCE_DIR}/src/common/eventos/EventoAcelerar.cpp
        ${CMAKE_SOURCE_DIR}/src/common/eventos/EventoDesacelerar.cpp
        ${CMAKE_SOURCE_DIR}/src/common/eventos/EventoFrenar.cpp
        ${CMAKE_SOURCE_DIR}/src/common/eventos/EventoDejarDeFrenar.cpp
        ${CMAKE_SOURCE_DIR}/src/common/eventos/EventoDoblarIzquierda.cpp
        ${CMAKE_SOURCE_DIR}/src/common/eventos/EventoDejarDeDoblarIzquierda.cpp
        ${CMAKE_SOURCE_DIR}/src/common/eventos/EventoDoblarDerecha.cpp
        ${CMAKE_SOURCE_DIR}/src/common/eventos/EventoDejarDeDoblarDerecha.cpp
        ${CMAKE_SOURCE_DIR}/src/common/eventos/EventoSnapshot.cpp
        ${CMAKE_SOURCE_DIR}/src/common/eventos/EventoFinCarrera.cpp
        ${CMAKE_SOURCE_DIR}/src/common/eventos/EventoAparecioConsumible.cpp
        ${CMAKE_SOURCE_DIR}/src/common/eventos/EventoDesaparecioConsumible.cpp
        ${CMAKE_SOURCE_DIR}/src/common/eventos/EventoChoque.cpp
        ${CMAKE_SOURCE_DIR}/src/common/eventos/EventoBarroPisado.cpp
        ${CMAKE_SOURCE_DIR}/src/common/eventos/EventoExplosion.cpp
        ${CMAKE_SOURCE_DIR}/src/common/eventos/EventoFinBarro.cpp
        ${CMAKE_SOURCE_DIR}/src/common/eventos/EventoPartidaCreada.cpp
        ${CMAKE_SOURCE_DIR}/src/common/eventos/EventoSnapshotLobby.cpp
        ${CMAKE_SOURCE_DIR}/src/common/eventos/EventoSnapshotSala.cpp
        ${CMAKE_SOURCE_DIR}/src/common/eventos/EventoUnirseASala.cpp
        ${CMAKE_SOURCE_DIR}/src/common/eventos/EventoFrenada.cpp
        ${CMAKE_SOURCE_DIR}/src/common/eventos/EventoFactory.cpp
        ${CMAKE_SOURCE_DIR}/src/common/red/SocketTCP.cpp
        ${CMAKE_SOURCE_DIR}/src/common/red/Protocolo.cpp
        ${CMAKE_SOURCE_DIR}/src/common/excepciones/EventoDesconocidoError.cpp
        )

include_directories(${CMAKE_SOURCE_DIR})
add_library(${PROJECT_NAME} STATIC ${SOURCES})
