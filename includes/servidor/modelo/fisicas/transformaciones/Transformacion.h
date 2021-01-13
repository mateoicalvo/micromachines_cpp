#ifndef _TRANSFORMACION_H_
#define _TRANSFORMACION_H_

//Forward declaration
class Fisicas;

class Transformacion {
protected:
    Fisicas& fisicas_;

public:
    Transformacion(Fisicas& unasFisicas);
    virtual ~Transformacion();
    virtual void aplicar() = 0;
};

#endif
