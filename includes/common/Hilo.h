#ifndef _THREAD_H_
#define _THREAD_H_

#include <thread>
#include <atomic>

class Hilo {
private:
    std::thread hilo_;
 
protected:
    std::atomic<bool> seguirCorriendo_;

public:
    Hilo();
    
    void iniciar();

    void dormir(double milisegundos);

    bool estaCorriendo();

    virtual void correr() = 0;

    // TODO: Refactorizar y hacer un detener default, virtual. Que solo lo overridee un hilo que lance mas hilos.
    virtual void detener() = 0;

    virtual void join();

    virtual ~Hilo();

    Hilo(const Hilo&) = delete;

    Hilo& operator=(const Hilo&) = delete;

    Hilo(Hilo&& other);

    Hilo& operator=(Hilo&& other);
};

#endif
