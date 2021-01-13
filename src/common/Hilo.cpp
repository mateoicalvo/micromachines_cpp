#include "includes/common/Hilo.h"

#include <thread>
#include <chrono>

Hilo::Hilo()
    : seguirCorriendo_(false) {
}

Hilo::~Hilo() {
}

bool Hilo::estaCorriendo() {
    return seguirCorriendo_;
}

Hilo::Hilo(Hilo&& otroHilo) {
    hilo_ = std::move(otroHilo.hilo_);
}

Hilo& Hilo::operator=(Hilo&& otroHilo) {
    hilo_ = std::move(otroHilo.hilo_);
    return *this;
}

void Hilo::iniciar() {
    seguirCorriendo_ = true;
    hilo_ = std::thread(&Hilo::correr, this);
}

void Hilo::dormir(double milisegundos) {
    std::this_thread::sleep_for(std::chrono::milliseconds((uint32_t)milisegundos));
}

void Hilo::join() {
    if (hilo_.joinable()) {
        hilo_.join();
    }   
}
