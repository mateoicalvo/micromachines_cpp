#ifndef _EVENTO_DESCONOCIDO_ERROR_H_
#define _EVENTO_DESCONOCIDO_ERROR_H_

#include <stdexcept>
#include <string>

class EventoDesconocidoError : public std::runtime_error {
public:
    EventoDesconocidoError(const std::string& mensaje);
};

#endif
