#ifndef _SUPERFICIE_FACTORY_H_
#define _SUPERFICIE_FACTORY_H_

#include <memory>

#include "includes/servidor/modelo/superficies/Superficie.h"
#include "includes/servidor/modelo/superficies/SuperficieTierra.h"
#include "includes/servidor/modelo/superficies/SuperficiePista.h"
#include "includes/servidor/modelo/superficies/SuperficieArena.h"

#define MENSAJE_ERROR_SUPERFICIE_DESCONOCIDA "Error al instanciar la superficie, se utilizó un UUID desconocido."

class SuperficieFactory {
private:
public:
    static std::shared_ptr<Superficie> instanciar(int uuid);
};

#endif
