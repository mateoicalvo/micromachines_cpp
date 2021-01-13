#include "includes/common/excepciones/EventoDesconocidoError.h"

EventoDesconocidoError::EventoDesconocidoError(const std::string& mensaje) :
    std::runtime_error(mensaje.c_str()) {

}
