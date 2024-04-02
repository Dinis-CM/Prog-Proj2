#include "leitura.c"
#include "calculo.c"
#include "mostra.c"
#include "seleciona.c"
#include "ordena.c"
#include "memoria.c"


int main(int argc, char *argv[])
{
	/*Inicializção das listas de aeroportos, rotas e escalas*/
    ListaAero *topo_aero = NULL;
    ListaRotas *topo_rotas = NULL;
    ListaEscalas *topo_escalas = NULL;

    int n_escala=-1, count=0;
	
    /*Numero de escalas*/    
    if(argc > 4){
        if( sscanf(argv[4], "%d", &n_escala) != 1 || n_escala < 0 || n_escala > 2){
            printf("Parâmetros inválidos \n");
            return 1;                
        }
    }  

    /*Leitura dos ficheiros*/
    leitura("aeroportos.txt", &topo_aero, &topo_rotas);
    leitura("rotas.txt", &topo_aero, &topo_rotas);

	/*Possiveis pedidos do utilizador*/
    switch(argc)
    {
        case 2:
			/*Lista de aeroportos*/
            if(strcmp(argv[1], "-aeroportos")==0){
                Mostra_lista_aero(topo_aero);
                liberta_memoria(topo_aero, topo_rotas, topo_escalas);
                return 0;        
            }
			/*Lista de rotas*/	
            else if(strcmp(argv[1], "-voos")==0){ 
                Mostra_lista_rotas(topo_rotas); 
                liberta_memoria(topo_aero, topo_rotas, topo_escalas); 
                return 0;
            }
            break;

        case 5:
			/*Lista de voos com escalas*/
            if(strcmp(argv[1], argv[2])!=0 && strlen(argv[1])==3 && strlen(argv[2])==3 && strcmp(argv[3], "-L")==0 && strlen(argv[4])==1  && 'A'<=argv[1][0] && argv[1][0]<='Z' && 'A'<=argv[1][1] && argv[1][1]<='Z' && 'A'<=argv[1][2] && argv[1][2]<='Z' && 'A'<=argv[2][0] && argv[2][0]<='Z' && 'A'<=argv[2][1] && argv[2][1]<='Z' && 'A'<=argv[2][2] && argv[2][2]<='Z'){
                topo_escalas = Seleciona_lista(topo_rotas, argv[1], argv[2], n_escala);
                Mostra_lista_escalas(topo_escalas, n_escala);
                liberta_memoria(topo_aero, topo_rotas, topo_escalas);
                return 0; 
            }
            break;
		case 6:
			/*Lista de voos com escala e ordenacao por ordem de partida ou selecao distância mais curta*/
            if(strcmp(argv[1], argv[2])!=0 && strlen(argv[1])==3 && strlen(argv[2])==3 && strcmp(argv[3], "-L")==0 && strlen(argv[4])==1  && ( strlen(argv[5])==2 || strlen(argv[5])==3) && 'A'<=argv[1][0] && argv[1][0]<='Z' && 'A'<=argv[1][1] && argv[1][1]<='Z' && 'A'<=argv[1][2] && argv[1][2]<='Z' && 'A'<=argv[2][0] && argv[2][0]<='Z' && 'A'<=argv[2][1] && argv[2][1]<='Z' && 'A'<=argv[2][2] && argv[2][2]<='Z'){
                topo_escalas = Seleciona_lista(topo_rotas, argv[1], argv[2], n_escala);
                count = Ordena_lista(&topo_escalas, argv[5], n_escala);
                if(count==1)                
                    return 1;
                Mostra_lista_escalas(topo_escalas, n_escala); 
                liberta_memoria(topo_aero, topo_rotas, topo_escalas);
                return 0;               
            }
            break;

        case 7:
			/*Lista de voos com escala e ordenacaoo por ordem de partida e selecao por distância mais curta*/
            if(strcmp(argv[1], argv[2])!=0 && strlen(argv[1])==3 && strlen(argv[2])==3 && strcmp(argv[3], "-L")==0 && strlen(argv[4])==1  && strlen(argv[5])==3 && strlen(argv[6])==2 && 'A'<=argv[1][0] && argv[1][0]<='Z' && 'A'<=argv[1][1] && argv[1][1]<='Z' && 'A'<=argv[1][2] && argv[1][2]<='Z' && 'A'<=argv[2][0] && argv[2][0]<='Z' && 'A'<=argv[2][1] && argv[2][1]<='Z' && 'A'<=argv[2][2] && argv[2][2]<='Z'){
                topo_escalas = Seleciona_lista(topo_rotas, argv[1], argv[2], n_escala);
                Ordena_lista(&topo_escalas, argv[5], n_escala);
                if(count==1)                
                    return 1;
                Ordena_lista(&topo_escalas, argv[6], n_escala);  
                if(count==1)                
                    return 1;              
                Mostra_lista_escalas(topo_escalas, n_escala); 
                liberta_memoria(topo_aero, topo_rotas, topo_escalas);
                return 0;                
            }
            break;
    }

    liberta_memoria(topo_aero, topo_rotas, topo_escalas);
	/*Leitura dos argumentos do utilizador invalida*/
    printf("Parâmetros inválidos \n");
    return 1;
}

