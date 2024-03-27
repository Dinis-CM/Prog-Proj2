#include "funcoes.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int main(int argc, char *argv[ ])
{

    ListaAero *topo_aero = NULL;
    ListaAero *ap_reg_anterior_aero = NULL;

    ListaRotas *topo_rotas = NULL;
    ListaRotas *ap_reg_anterior_rotas = NULL;
    
    leitura("aeroportos.txt", &topo_aero, &topo_rotas, &ap_reg_anterior_aero,  &ap_reg_anterior_rotas);
    leitura("rotas.txt", &topo_aero, &topo_rotas, &ap_reg_anterior_aero,  &ap_reg_anterior_rotas);       
    
    switch(argc)
    {
        case 2:
            if(strcmp(argv[1], "-aeroportos")==0){
                Mostra_lista_aero(topo_aero);        
            }
            else if(strcmp(argv[1], "-voos")==0){ 
                Mostra_lista_rotas(topo_rotas);  
            }
            break;

        case 5:
            if(strcmp(argv[3], "-L")==0 && strlen(argv[1])==3 && strlen(argv[2])==3 ){
                Seleciona_lista(&topo_rotas, ap_reg_anterior_rotas, argv[1], argv[2], argv[4]);
                Mostra_lista_rotas(topo_rotas); 
            }
            break;

    }
    return 0;
}

