#include "includes/cliente/utils/ConfigCliente.h"

#include <fstream>

ConfigCliente &ConfigCliente::instancia() {
  static ConfigCliente config_(RUTA_CONFIG_CLIENTE);
  return config_;
}

ConfigCliente::ConfigCliente(const std::string &rutaArchivo) {
  std::ifstream archivo(rutaArchivo);
  archivo >> json_;
}

unsigned int ConfigCliente::anchoVentana() {
  return json_["ventana"]["ancho"].get<unsigned int>();
}

unsigned int ConfigCliente::altoVentana() {
  return json_["ventana"]["alto"].get<unsigned int>();
}

float ConfigCliente::factorLejaniaCamara() {
  return json_["factorLejaniaPista"].get<float>();
}

bool ConfigCliente::pantallaCompleta() {
  return json_["ventana"]["pantallaCompleta"].get<bool>();
}

std::string ConfigCliente::tituloVentana() {
  return std::move(json_["ventana"]["titulo"].get<std::string>());
}

unsigned int ConfigCliente::fps() {
  return json_["ventana"]["fps"].get<unsigned int>();
}

std::string ConfigCliente::host() {
  return std::move(json_["red"]["host"].get<std::string>());
}

std::string ConfigCliente::puerto() {
  return std::move(json_["red"]["puerto"].get<std::string>());
}

std::string ConfigCliente::fuente() {
  return std::move(json_["fuente"]["path"].get<std::string>());
}

std::string ConfigCliente::musicaAmbiente() {
  return std::move(json_["musica"]["ambiente"].get<std::string>());
}

std::string ConfigCliente::musicaMotor() {
  return std::move(json_["musica"]["motor"].get<std::string>());
}

std::string ConfigCliente::musicaExplosion() {
  return std::move(json_["musica"]["explosion"].get<std::string>());
}

std::string ConfigCliente::musicaVacio() {
  return std::move(json_["musica"]["empty"].get<std::string>());
}

std::string ConfigCliente::musicaChoque() {
  return std::move(json_["musica"]["choque"].get<std::string>());
}

std::string ConfigCliente::musicaFrenada() {
  return std::move(json_["musica"]["frenada"].get<std::string>());
}

std::string ConfigCliente::rutaLuaScriptUsuario() {
  return std::move(json_["lua"]["ruta2"].get<std::string>());
}

std::string ConfigCliente::rutaLuaScript() {
  return std::move(json_["lua"]["ruta"].get<std::string>());
}

int ConfigCliente::tiempoReaccionHumano() {
  return json_["lua"]["tiempoHumano"].get<int>();
}

unsigned int ConfigCliente::volumenAmbiente() {
  return json_["volumen"]["ambiente"].get<unsigned int>();
}

unsigned int ConfigCliente::anchoBloquesPista() {
  return json_["bloques"]["ancho"].get<unsigned int>();
}

unsigned int ConfigCliente::altoBloquesPista() {
  return json_["bloques"]["alto"].get<unsigned int>();
}

double ConfigCliente::pixelPorMetro() {
  return json_["conversor"]["pixelPorMetro"].get<double>();
}

unsigned int ConfigCliente::pixelPorBloque() {
  return json_["conversor"]["pixelPorBloque"].get<unsigned int>();
}

std::string ConfigCliente::texto(std::string sector) {
  return std::move(json_["interfaz"][sector]["texto"].get<std::string>());
}

unsigned int ConfigCliente::tamanioTexto(std::string sector) {
  return json_["interfaz"][sector]["tamañoTexto"].get<unsigned int>();
}

unsigned int ConfigCliente::anchoTexto(std::string sector) {
  return json_["interfaz"][sector]["anchoTexto"].get<unsigned int>();
}

double ConfigCliente::margenX(std::string sector) {
  return json_["interfaz"][sector]["margenX"].get<double>();
}

double ConfigCliente::margenY(std::string sector) {
  return json_["interfaz"][sector]["margenY"].get<double>();
}

unsigned int ConfigCliente::uuid(std::string nombreAnimacion) {
  return json_["animaciones"][nombreAnimacion]["uuid"].get<unsigned int>();
}

unsigned int ConfigCliente::ancho(std::string nombreAnimacion) {
  return json_["animaciones"][nombreAnimacion]["ancho"].get<unsigned int>();
}

unsigned int ConfigCliente::alto(std::string nombreAnimacion) {
  return json_["animaciones"][nombreAnimacion]["alto"].get<unsigned int>();
}

std::vector<std::string> ConfigCliente::sprites(std::string nombreAnimacion) {
  return std::move(json_["animaciones"][nombreAnimacion]["sprites"].get<std::vector<
      std::string>>());
}

unsigned int ConfigCliente::anchoGrabadora() {
  return json_["grabadora"]["resolucion"]["ancho"].get<unsigned int>();
}

unsigned int ConfigCliente::altoGrabadora() {
  return json_["grabadora"]["resolucion"]["alto"].get<unsigned int>();
}

std::string ConfigCliente::formatoGrabadora() {
  return std::move(json_["grabadora"]["formato"].get<std::string>());
}

unsigned int ConfigCliente::fpsGrabadora() {
  return json_["grabadora"]["fps"].get<unsigned int>();
}

uint32_t ConfigCliente::bitrateGrabadora() {
  return json_["grabadora"]["bitrate"].get<uint32_t>();
}
