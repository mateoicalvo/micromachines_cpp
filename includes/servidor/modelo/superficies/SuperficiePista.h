#ifndef _SUPERFICIE_PISTA_H_
#define _SUPERFICIE_PISTA_H_

#include "includes/servidor/modelo/superficies/Superficie.h"

class SuperficiePista : public Superficie {

public:
    virtual int getTipo() override;
};

#endif
