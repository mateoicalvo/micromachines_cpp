#ifndef _COLISIONABLE_H_
#define _COLISIONABLE_H_

class Colisionable {
private:
    bool yaColisionado_;

public:
    Colisionable();
    virtual ~Colisionable();
    enum tipos {
        VEHICULO_ = 0,
        BARRO_ = 1,
        ACEITE_ = 2,
        PIEDRA_ = 3,
        SALUD_ = 4,
        BOOST_ = 5,
        SUPERFICIE_ARENA_ = 6,
        SUPERFICIE_PISTA_ = 7,
        SUPERFICIE_TIERRA_ = 8,
        CHECKPOINT_ = 9,
        META_ = 10
    };
    
    virtual int getTipo() = 0;
    void colisionado();
    bool yaFueColisionado();
};

#endif
