#ifndef _CONFIG_CLIENTE_H_
#define _CONFIG_CLIENTE_H_

#define RUTA_CONFIG_CLIENTE "config/client_settings.json"

#define CONFIG_CLIENTE ConfigCliente::instancia()

#include <string>
#include <vector>

#include "includes/3rd-party/jsoncpp/json.hpp"

class ConfigCliente {
 private:
  ConfigCliente(const std::string &rutaArchivo);
  Json json_;

 public:
  static ConfigCliente &instancia();

  unsigned int anchoVentana();
  unsigned int altoVentana();
  float factorLejaniaCamara();
  bool pantallaCompleta();
  std::string tituloVentana();
  unsigned int fps();

  std::string host();
  std::string puerto();

  std::string fuente();

  std::string musicaAmbiente();
  std::string musicaMotor();
  std::string musicaExplosion();
  std::string musicaVacio();
  std::string musicaChoque();
  std::string musicaFrenada();

  unsigned int volumenAmbiente();

  unsigned int anchoBloquesPista();
  unsigned int altoBloquesPista();

  double pixelPorMetro();
  unsigned int pixelPorBloque();

  std::string texto(std::string sector);
  unsigned int tamanioTexto(std::string sector);
  unsigned int anchoTexto(std::string sector);
  double margenX(std::string sector);
  double margenY(std::string sector);

  unsigned int uuid(std::string nombreAnimacion);
  unsigned int ancho(std::string nombreAnimacion);
  unsigned int alto(std::string nombreAnimacion);
  std::vector<std::string> sprites(std::string nombreAnimacion);

  unsigned int anchoGrabadora();
  unsigned int altoGrabadora();
  std::string formatoGrabadora();
  uint32_t fpsGrabadora();
  unsigned int bitrateGrabadora();



  std::string rutaLuaScriptUsuario();
  std::string rutaLuaScript();
  int tiempoReaccionHumano();
};

#endif
