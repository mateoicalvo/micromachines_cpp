#include <iostream>

#include "includes/servidor/Servidor.h"
#include "includes/servidor/utils/ConfigServidor.h"

int main(int argc, char const *argv[]) {
    Servidor servidor(CONFIG_SERVIDOR.hostServidor(), CONFIG_SERVIDOR.puertoServidor());
    try {
        servidor.correr();
    } catch(const std::exception& e) {
        std::cout << e.what() << '\n';
    }
    servidor.cerrar();
    return 0;
}
