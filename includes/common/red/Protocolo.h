#ifndef _PROTOCOLO_H_
#define _PROTOCOLO_H_

#include "includes/common/red/SocketTCP.h"

#define LEN_8 1
#define LEN_16 2
#define LEN_32 4

class Protocolo {
private:
    SocketTCP& socket_;
public:
    Protocolo(SocketTCP& socket);
    uint8_t recibirNumUnsigned8();
    uint16_t recibirNumUnsigned16();
    uint32_t recibirNumUnsigned32();
    void enviar(uint16_t numero);
    void enviar(uint8_t numero);
    void enviar(uint32_t numero);
    

};

#endif
