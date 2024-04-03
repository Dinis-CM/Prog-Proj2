#include "leitura.c"
#include "calculo.c"
#include "mostra.c"
#include "seleciona.c"
#include "ordena.c"
#include "memoria.c"
#include "opcoes.c"


int main(int argc, char *argv[])
{
	/*Inicializção das listas de aeroportos, rotas e escalas*/
    ListaAero *topo_aero = NULL;
    ListaRotas *topo_rotas = NULL;
    ListaEscalas *topo_escalas = NULL;

    int opcoes;

    /*Leitura dos ficheiros*/
    leitura("aeroportos.txt", &topo_aero, &topo_rotas);
    leitura("rotas.txt", &topo_aero, &topo_rotas);

    opcoes = escolha_opcoes(topo_aero, topo_rotas, topo_escalas, argc, argv);

    liberta_memoria(topo_aero, topo_rotas, topo_escalas);

    /*Leitura dos argumentos do utilizador invalida*/
	if(opcoes==1){
        printf("Parâmetros inválidos \n");
        return 1;    
    }

    return 0;
}

