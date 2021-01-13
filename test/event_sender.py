import socket, struct
def main():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect(('localhost', 10001))
    while True:
        entrada = input()
        if entrada is 'q':
            break
        s.send(struct.pack(">H", int(entrada)))
    
    while True:
        entrada = input()
        if entrada is 'q':
            break
        uuidEventoRed = s.recv(2)
        uuidEvento = struct.unpack(">H", uuidEventoRed)[0]
        print("UUIDEVENTO: {}".format(uuidEvento))
        if (uuidEvento is 14): #EventoIDVehiculo
            miIDRed = s.recv(1)
            miID = struct.unpack(">B", miIDRed)[0]
            print("Mi vehiculo id es {}".format(miID))

        if (uuidEvento is 15): #Evento snapshot
            nVehiculosRed = s.recv(1)
            nVehiculos = struct.unpack(">B", nVehiculosRed)[0]
            print("N Vehiculos: {}".format(nVehiculos))
            idAutitoRed = s.recv(1)
            idAutito = struct.unpack(">B", idAutitoRed)[0]
            print("Soy el autito: {}".format(idAutito))
            xRed = s.recv(2)
            x = struct.unpack(">H", xRed)[0]
            print("X: {}".format(x))
            yRed = s.recv(2)
            y = struct.unpack(">H", yRed)[0]
            print("Y: {}".format(y))
            anguloRed = s.recv(2)
            angulo = struct.unpack(">H", anguloRed)[0]
            print("Angulo: {}".format(angulo))
            vidaRed = s.recv(1)
            vida = struct.unpack(">B", vidaRed)[0]
            print("Vida: {}".format(vida))
            visibleRed = s.recv(1)
            visible = struct.unpack(">B", visibleRed)[0]
            print("Visible: {}".format(visible))

    s.close()

main()