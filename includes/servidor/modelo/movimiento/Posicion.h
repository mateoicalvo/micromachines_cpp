#ifndef _POSICION_H_
#define _POSICION_H_

#include <cstdint>

class Posicion {
public:
    float x_;
    float y_;
    uint16_t anguloDeg_;

    Posicion(float x, float y, uint16_t anguloDeg);
};

#endif
