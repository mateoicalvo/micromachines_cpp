#include "includes/common/Cronometro.h"

#include <chrono>

double Cronometro::ahora() {
    auto ahora = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now());
    return ahora.time_since_epoch().count();
}
