#include "header.h"

int escolha_opcoes(ListaAero *topo_aero, ListaRotas *topo_rotas, ListaEscalas *topo_escalas, int argc, char* argv[]){

    int n_escala=-1, count=0;
	
    /*Verificacoa do numero de escalas*/    
    if(argc > 4){
        if(sscanf(argv[4], "%d", &n_escala) != 1 || n_escala < 0 || n_escala > 2){
            printf("Parâmetros inválidos \n");
            return 1;                
        }
    }  

	/*Possiveis pedidos do utilizador*/
    if(argc==2 && strcmp(argv[1], "-aeroportos")==0){
        Mostra_lista_aero(topo_aero);
        return 0;    
    }

    else if(argc==2 && strcmp(argv[1], "-voos")==0){ 
        Mostra_lista_rotas(topo_rotas); 
        return 0;    
    }

    else if(argc==5 && strcmp(argv[1], argv[2])!=0 && strlen(argv[1])==3 && strlen(argv[2])==3 && strcmp(argv[3], "-L")==0 && strlen(argv[4])==1  && 'A'<=argv[1][0] && argv[1][0]<='Z' && 'A'<=argv[1][1] && argv[1][1]<='Z' && 'A'<=argv[1][2] && argv[1][2]<='Z' && 'A'<=argv[2][0] && argv[2][0]<='Z' && 'A'<=argv[2][1] && argv[2][1]<='Z' && 'A'<=argv[2][2] && argv[2][2]<='Z'){               
        topo_escalas = Seleciona_lista(topo_rotas, argv[1], argv[2], n_escala);
        Mostra_lista_escalas(topo_escalas, n_escala);
        return 0; 
    
    }
    
    /*Mostra e ordena as escalas de acordo com o código de classificação fornecido e os aeroportos fornecidos*/
    else if(argc==6 && strcmp(argv[1], argv[2])!=0 && strlen(argv[1])==3 && strlen(argv[2])==3 && strcmp(argv[3], "-L")==0 && strlen(argv[4])==1  && ( strlen(argv[5])==2 || strlen(argv[5])==3) && 'A'<=argv[1][0] && argv[1][0]<='Z' && 'A'<=argv[1][1] && argv[1][1]<='Z' && 'A'<=argv[1][2] && argv[1][2]<='Z' && 'A'<=argv[2][0] && argv[2][0]<='Z' && 'A'<=argv[2][1] && argv[2][1]<='Z' && 'A'<=argv[2][2] && argv[2][2]<='Z'){
        topo_escalas = Seleciona_lista(topo_rotas, argv[1], argv[2], n_escala);
        count = Ordena_lista(&topo_escalas, argv[5], n_escala);
        if(count==1)                
            return 1;
        Mostra_lista_escalas(topo_escalas, n_escala); 
        return 0; 

    }

    /*Mostra e ordena as escalas de acordo com o código de classificação fornecido, com os aeroportos fornecidos e as companhias*/
    else if(argc==7 && strcmp(argv[1], argv[2])!=0 && strlen(argv[1])==3 && strlen(argv[2])==3 && strcmp(argv[3], "-L")==0 && strlen(argv[4])==1  && strlen(argv[5])==3 && strlen(argv[6])==2 && 'A'<=argv[1][0] && argv[1][0]<='Z' && 'A'<=argv[1][1] && argv[1][1]<='Z' && 'A'<=argv[1][2] && argv[1][2]<='Z' && 'A'<=argv[2][0] && argv[2][0]<='Z' && 'A'<=argv[2][1] && argv[2][1]<='Z' && 'A'<=argv[2][2] && argv[2][2]<='Z'){
        topo_escalas = Seleciona_lista(topo_rotas, argv[1], argv[2], n_escala);
        Ordena_lista(&topo_escalas, argv[5], n_escala);
        if(count==1)                
            return 1;
        Ordena_lista(&topo_escalas, argv[6], n_escala);  
        if(count==1)                
            return 1;              
        Mostra_lista_escalas(topo_escalas, n_escala); 
        return 0;    
    }

    return 1;
}