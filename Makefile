#Compiler
CC = gcc

#Compiler flags
FLAG = -Wall -pedantic -ansi -lm -g

# Executable
default: rotas2024

# Linking
rotas2024: main.o leitura.o calculo.o mostra.o ordena.o seleciona.o memoria.o opcoes.o
	$(CC) main.c -o rotas2024 $(FLAG)

# Compilation
opcoes.o: opcoes.c
	$(CC) -c opcoes.c

memoria.o: memoria.c
	$(CC) -c memoria.c

seleciona.o: seleciona.c
	$(CC) -c seleciona.c

ordena.o: ordena.c
	$(CC) -c ordena.c

mostra.o: mostra.c
	$(CC) -c mostra.c

calculo.o: calculo.c
	$(CC) -c calculo.c

leitura.o: leitura.c
	$(CC) -c leitura.c

main.o: main.c
	$(CC) -c main.c

# Cleanup
clean:
	$(RM) rotas2024 *.o *~


