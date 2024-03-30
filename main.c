#include "leitura.c"
#include "calculo.c"
#include "mostra.c"
#include "seleciona.c"
#include "ordena.c"


int main(int argc, char *argv[])
{
	//Inicializção das listas de aeroportos, rotas e escalas
    ListaAero *topo_aero = NULL;
    ListaRotas *topo_rotas = NULL;
    ListaEscalas *topo_escalas = NULL;
	
    //Leitura dos ficheiros
    leitura("aeroportos.txt", &topo_aero, &topo_rotas);
    leitura("rotas.txt", &topo_aero, &topo_rotas);       

	//Possiveis pedidos do utilizador
    switch(argc)
    {
        case 2:
			//Lista de aeroportos
            if(strcmp(argv[1], "-aeroportos")==0){
                Mostra_lista_aero(topo_aero);
                return 0;        
            }
			//Lista de rotas	
            else if(strcmp(argv[1], "-voos")==0){ 
                Mostra_lista_rotas(topo_rotas);  
                return 0;
            }
            break;

        case 5:
			//Lista de voos com escalas
            if(strcmp(argv[3], "-L")==0 && strlen(argv[1])==3 && strlen(argv[2])==3 && strlen(argv[4])==1){
                topo_escalas = Seleciona_lista(topo_rotas, argv[1], argv[2], argv[4]);
                Mostra_lista_escalas(topo_escalas, argv[4]);
                return 0; 
            }
            break;
		case 6:
			//Lista de voos com escala e ordenacao por ordem de partida ou selecao distância mais curta
            if(strcmp(argv[3], "-L")==0 && strlen(argv[1])==3 && strcmp(argv[1], argv[2])!=0 && strlen(argv[2])==3 && strlen(argv[4])==1 && ( strlen(argv[5])==2 || strlen(argv[5])==3)){
                topo_escalas = Seleciona_lista(topo_rotas, argv[1], argv[2], argv[4]);
                Ordena_lista(&topo_escalas, argv[5]);                
                Mostra_lista_escalas(topo_escalas, argv[4]); 
                return 0;               
            }
            break;

        case 7:
			//Lista de voos com escala e ordenacaoo por ordem de partida e selecao por distância mais curta
            if(strcmp(argv[3], "-L")==0 && strlen(argv[1])==3 && strcmp(argv[1], argv[2])!=0 && strlen(argv[2])==3 && strlen(argv[4])==1 && ( strlen(argv[5])==2 || strlen(argv[5])==3) && ( strlen(argv[6])==2 || strlen(argv[6])==3)){
                topo_escalas = Seleciona_lista(topo_rotas, argv[1], argv[2], argv[4]);
                Ordena_lista(&topo_escalas, argv[5]);
                Ordena_lista(&topo_escalas, argv[6]);                
                Mostra_lista_escalas(topo_escalas, argv[4]); 
                return 0;                
            }
            break;
    }
	//Leitura dos argumentos do utilizador invalida
    printf("Parâmetros inválidos \n");
    return 1;
}

