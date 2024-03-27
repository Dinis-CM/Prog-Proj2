# Executable
default: rotas2024

# Linking
rotas2024: main.o funcoes.o
	gcc -g main.c -o rotas2024 -lm

# Compilation
funcoes.o: funcoes.c
	gcc -c funcoes.c

main.o: main.c
	gcc -c main.c

# Cleanup
clean:
	$(RM) rotas2024 *.o *~


