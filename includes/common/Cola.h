#ifndef _COLA_H_
#define _COLA_H_

#include <queue>

template <class T>
class Cola {
private:
    Cola(Cola&& otra) = delete;
    Cola(const Cola& otra) = delete;
    Cola& operator=(const Cola& otra) = delete;
    Cola& operator=(Cola&& otra) = delete;

public:
    Cola() {
    }
    virtual ~Cola() {
    }

    virtual void put(T unElemento) = 0;
    
    virtual bool get(T& unElemento) = 0;
};

#endif
