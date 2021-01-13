#ifndef _SDL_EXCEPTION_H_
#define _SDL_EXCEPTION_H_

#include <string>
#include <exception>

class SDLException : public std::exception {
private:
    std::string descripcion_;

public:
    SDLException(const char* descripcion, const char* errorSDL);
    const char* what() const noexcept;
};

#endif
