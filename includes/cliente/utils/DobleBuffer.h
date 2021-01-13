#ifndef _DOBLE_BUFFER_H_
#define _DOBLE_BUFFER_H_


#include <mutex>
#include <condition_variable>
#include <atomic>

template <typename T>
class DobleBuffer {
private:
    T datos_[2];
    int actual_{0};
    std::mutex mutex_;
    std::condition_variable cond_;
    std::atomic<bool> detenido_, nuevo_dato_;
public:
    DobleBuffer() : detenido_(false), nuevo_dato_(false) {}
    ~DobleBuffer() {}

    void swap();
    void set(T&& instance);
    bool get(T& destino);
    void detener();
};


template <typename T>
void DobleBuffer<T>::set(T&& instance) {
    std::unique_lock<std::mutex> lock(mutex_);
    datos_[!actual_] = std::move(instance);
    nuevo_dato_ = true;
    cond_.notify_one();
}


template <typename T>
bool DobleBuffer<T>::get(T& destino) {
    std::unique_lock<std::mutex> lck(mutex_);
    cond_.wait(lck, [this]{return nuevo_dato_ || detenido_;});
    if (detenido_) {
        nuevo_dato_ = detenido_ = false;
        return false;
    }
    actual_ = !actual_;
    destino = datos_[actual_];
    nuevo_dato_ = false;
    return true;
}

template <typename T>
void DobleBuffer<T>::detener(){
    detenido_ = true;
    cond_.notify_all();
}



#endif
