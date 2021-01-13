#ifndef _TIERRA_H_
#define _TIERRA_H_

#include "includes/servidor/modelo/superficies/Superficie.h"

class SuperficieTierra : public Superficie {

public:
    virtual int getTipo() override;
};

#endif
