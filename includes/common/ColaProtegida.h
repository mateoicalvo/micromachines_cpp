#ifndef _COLA_PROTEGIDA_H_
#define _COLA_PROTEGIDA_H_

#include <mutex>

#include "includes/common/Cola.h"

template <class T>
class ColaProtegida : public Cola<T> {
private:
    std::mutex mtx_;

    ColaProtegida(ColaProtegida&& otra) = delete;

    ColaProtegida(const ColaProtegida& otra) = delete;

    ColaProtegida& operator=(const ColaProtegida& otra) = delete;

    ColaProtegida& operator=(ColaProtegida&& otra) = delete;

    std::queue<T> elementos_;

    public:
    ColaProtegida() {
    }

    ~ColaProtegida() {
    }

    void put(T unElemento) override {
        std::lock_guard<std::mutex> lck(mtx_);
        elementos_.push(unElemento);
    }
    
    bool get(T& unElemento) override {
        std::unique_lock<std::mutex> lck(mtx_);
        if (elementos_.empty()) {
            return false;
        }
        unElemento = elementos_.front();
        elementos_.pop();
        return true;
    }
};

#endif
