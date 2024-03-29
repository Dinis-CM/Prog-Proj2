# Executable
default: rotas2024

# Linking
rotas2024: main.o leitura.o calculo.o mostra.o ordena.o seleciona.o
	gcc -g main.c -o rotas2024 -lm

# Compilation
seleciona.o: seleciona.c
	gcc -c seleciona.c

ordena.o: ordena.c
	gcc -c ordena.c

mostra.o: mostra.c
	gcc -c mostra.c

calculo.o: calculo.c
	gcc -c calculo.c

leitura.o: leitura.c
	gcc -c leitura.c

main.o: main.c
	gcc -c main.c

# Cleanup
clean:
	$(RM) rotas2024 *.o *~


