#include <iostream>

#include "includes/cliente/Cliente.h"
#include "includes/cliente/utils/ConfigCliente.h"

int main(int argc, char *argv[]) {
    Cliente cliente(CONFIG_CLIENTE.anchoVentana(), CONFIG_CLIENTE.altoVentana(), CONFIG_CLIENTE.pantallaCompleta(), CONFIG_CLIENTE.tituloVentana(), CONFIG_CLIENTE.host(), CONFIG_CLIENTE.puerto());
    try {
        cliente.correr();
    } catch(const std::exception& e) {
        std::cout << e.what() << '\n';
        return -1;
    }
    cliente.cerrar();
    return 0;
}
