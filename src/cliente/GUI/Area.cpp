#include "includes/cliente/GUI/Area.h"

Area::Area(unsigned int x, unsigned int y, unsigned int ancho, unsigned int alto) :
    x_(x),
    y_(y),
    ancho_(ancho),
    alto_(alto) {

}

unsigned int Area::ancho() {
    return ancho_;
}

unsigned int Area::alto() {
    return alto_;
}

unsigned int Area::x() {
    return x_;
}

unsigned int Area::y() {
    return y_;
}
