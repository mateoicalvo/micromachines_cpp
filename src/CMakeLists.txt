cmake_minimum_required(VERSION 3.10.2)

find_package(Lua REQUIRED)

message("Variables:\n")

include_directories(${LUA_INCLUDE_DIR})

# Subdirectorios 3rd-party que se compilan sin flags
add_subdirectory(3rd-party/Box2D)
add_subdirectory(3rd-party/lua)


# Subdirectorios propios
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -D__STDC_CONSTANT_MACROS")

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/includes/3rd-party)

add_subdirectory(servidor)
add_subdirectory(cliente)

add_executable(Servidor servidor/main_servidor.cpp)
target_link_libraries(Servidor ServidorCMake Box2D)

add_executable(Cliente cliente/main_cliente.cpp)

target_link_libraries(Cliente ClienteCMake SDL2 SDL2_image SDL2_mixer SDL2_ttf avutil avformat avcodec swscale swresample z m lua_interprete lua5.3)

INSTALL(TARGETS Servidor DESTINATION ${RUTA_INSTALACION})
INSTALL(TARGETS Cliente DESTINATION ${RUTA_INSTALACION})
