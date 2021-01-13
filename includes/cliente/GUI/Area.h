#ifndef _AREA_H_
#define _AREA_H_

class Area {
private:
    unsigned int x_;
    unsigned int y_;
    unsigned int ancho_;
    unsigned int alto_;
public:
    Area(unsigned int x, unsigned int y, unsigned int ancho, unsigned int alto);

    unsigned int ancho();
    unsigned int alto();

    unsigned int x();
    unsigned int y();
};

#endif
