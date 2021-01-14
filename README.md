# micromachines
Clon del juego micromachines realizado en C++ & SDL2

## Librerias / programas necesarios

### Se instalan con apt install en ubuntu

build-essential

cmake

libsdl2-dev libsdl2-mixer-dev libsdl2-ttf-dev libsdl2-image-dev

lua5.3 liblua5.3-dev

libavutil-dev libavformat-dev libavcodec-dev libswscale-dev libswresample-dev

## Compilación

Clonar el repositorio.

Ubicarse en el directorio raíz

En una consola

  mkdir build

  cd build

  make install (se recomienda -jN con N el número de núcleos)
  
## Ejecución
Los ejecutables y assets necesarios se instalan en /home/user/NombreUsuario/micromachines

En una terminal en dicho directorio:
  
  ./Servidor
  
En otra terminal, mismo directorio:
  
  ./Cliente
  
## Configuración
Dentro de la carpeta config se encuentran los archivos de configuración del juego, permitiendo cambiar la IP del servidor, el puerto y parámetros jugables del servidor y el cliente.
