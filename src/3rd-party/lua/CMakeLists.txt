cmake_minimum_required(VERSION 2.6)
project(lua_interprete)

message("LUA_FOUND: ${LUA_FOUND}")
message("LUA_LIBRARIES: ${LUA_INCLUDE_DIR}")
message("LUA_INCLUDE_DIR: ${LUA_INCLUDE_DIR}")
message("LUA_VERSION_STRING: ${LUA_VERSION_STRING}")
message("LUA_VERSION_MAJOR: ${LUA_VERSION_MAJOR}")
message("LUA_VERSION_MINOR: ${LUA_VERSION_MINOR}")
message("LUA_VERSION_PATCH: ${LUA_VERSION_PATCH}")


find_package(Lua REQUIRED)

message("Variables:\n")

include_directories(${LUA_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/includes/3rd-party)
include_directories(${CMAKE_SOURCE_DIR})



set(SOURCES
  ${PROJECT_SOURCE_DIR}/lua/LuaInterprete.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})