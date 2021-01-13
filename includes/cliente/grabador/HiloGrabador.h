#ifndef __HILO_GRABADOR_H__
#define __HILO_GRABADOR_H__


#include "includes/common/Hilo.h"
#include "includes/cliente/utils/DobleBuffer.h"
#include <vector>


class HiloGrabador : public Hilo {
public:
    virtual void correr() override;

    virtual void detener() override;

    DobleBuffer<std::vector<char>>& getBuffer();

private:
	DobleBuffer<std::vector<char>> lineas_rgb_;
};

#endif
