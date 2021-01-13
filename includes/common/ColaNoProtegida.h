#ifndef _COLA_NO_PROTEGIDA_H_
#define _COLA_NO_PROTEGIDA_H_

#include "includes/common/Cola.h"

template <class T>
class ColaNoProtegida : public Cola<T> {
private:
    ColaNoProtegida(ColaNoProtegida&& otra) = delete;
    ColaNoProtegida(const ColaNoProtegida& otra) = delete;
    ColaNoProtegida& operator=(const ColaNoProtegida& otra) = delete;
    ColaNoProtegida& operator=(ColaNoProtegida&& otra) = delete;

    std::queue<T> elementos_;

    public:
    ColaNoProtegida() {
    }

    ~ColaNoProtegida() {
    }

    void put(T unElemento) override {
        elementos_.push(std::move(unElemento));
    }
    
    bool get(T& unElemento) override {
        if (elementos_.empty()) {
            return false;
        }
        unElemento = std::move(elementos_.front());
        elementos_.pop();
        return true;
    }
};

#endif
