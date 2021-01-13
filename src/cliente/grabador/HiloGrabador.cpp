#include "includes/cliente/grabador/HiloGrabador.h"

#include "includes/cliente/utils/ConfigCliente.h"
#include "includes/cliente/grabador/ffmpeg/output_video.h"
#include "includes/cliente/grabador/ffmpeg/output_format.h"

#include <ctime>
#include "includes/common/Cronometro.h"

#include <thread>
#include <chrono>

void HiloGrabador::correr(){
    time_t t = std::time(0);
	long int ahora = static_cast<long int> (t);
	std::string  nombreGrabacion = std::to_string(ahora) + std::string(".") + CONFIG_CLIENTE.formatoGrabadora();
    OutputFormat fmt(nombreGrabacion);
    AVRational frame_rate = { 1, static_cast<int>(CONFIG_CLIENTE.fpsGrabadora()) };
    OutputVideo videoOutput(fmt, frame_rate, CONFIG_CLIENTE.anchoGrabadora(), CONFIG_CLIENTE.altoGrabadora(), AV_PIX_FMT_RGB24);
    fmt.open();
    double frecuencia = (double) 1 / (double) CONFIG_CLIENTE.fpsGrabadora();
    int iteracion = 0;
    frecuencia *= 1000;
    Cronometro c;
    double t1 = c.ahora();				
	while (seguirCorriendo_){
        std::vector<char> linea;
        bool hayFrame = lineas_rgb_.get(linea);
        if (!hayFrame) {
            break;
        }
        videoOutput.rgb_line_to_frame(linea.data());
        videoOutput.write_frame();
        // Tiempo por frame
        double t2 = c.ahora();
        double resto = frecuencia - (t2 - t1);
        if (resto < 0) {
          double atraso = -resto;
          double perdidos = atraso - std::fmod(atraso, frecuencia);
          resto = frecuencia - std::fmod(atraso, frecuencia);
          t1 += perdidos;
          iteracion += std::floor(perdidos / frecuencia);
        }
        Hilo::dormir(resto);
        t1 += frecuencia;
        iteracion += 1;
	}   
	fmt.write_trailer();
	// Reinicio el doble buffer
    //FIXME: HACER UN VACIAR, no se pueden reasignar/mover mutexes. En realidad no es necesario vaciarlo
	//lineas_rgb_ = DobleBuffer<std::vector<char>>();
}


void HiloGrabador::detener(){
    seguirCorriendo_ = false;
    lineas_rgb_.detener();
}

DobleBuffer<std::vector<char>>& HiloGrabador::getBuffer() {
    return lineas_rgb_;
}
