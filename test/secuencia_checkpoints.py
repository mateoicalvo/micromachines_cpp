def main():
    
    secuencia = [x for x in range(0,9)]
    #Esto es uma delicia
    siguientes = [(t+1)%len(secuencia) for t in secuencia]

    print(secuencia)
    print(siguientes)

main()