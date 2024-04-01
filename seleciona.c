#include "header.h"

/*Decide quantas escalas estamos à procura*/
ListaEscalas* Seleciona_lista(ListaRotas *topo_rotas, char IATA_partida[3], char IATA_chegada[3], int n_escala){

    ListaEscalas *topo_escalas=NULL;

    if(n_escala==0)
        topo_escalas = Adiciona_voo_0_escalas(topo_escalas, topo_rotas, IATA_partida, IATA_chegada);
    
    else if(n_escala==1)
        topo_escalas = Adiciona_voo_1_escalas(topo_escalas, topo_rotas, IATA_partida, IATA_chegada);

    else if(n_escala==2)
        topo_escalas = Adiciona_voo_2_escalas(topo_escalas, topo_rotas, IATA_partida, IATA_chegada);
    else{
        printf("Parâmetros inválidos \n");
        exit(1);    
    }
    return topo_escalas;
}

/*Cria voos com  0 escalas*/
ListaEscalas* Adiciona_voo_0_escalas(ListaEscalas* topo_escalas, ListaRotas* topo_rotas, char IATA_partida[3], char IATA_chegada[3]){
        
    ListaRotas *aux = NULL;
    ListaEscalas *ap_local = NULL, *help = NULL;
   
    /*Passa por todos elementos da lista e verifica se o aeroporto de partida e chegada são os desejados*/
    for (aux = topo_rotas; aux != NULL; aux=aux->prox ){
        if (IATA_partida[0] == aux->x.IATA_partida[0] && IATA_partida[1] == aux->x.IATA_partida[1] && IATA_partida[2] == aux->x.IATA_partida[2] && IATA_chegada[0] == aux->x.IATA_chegada[0] && IATA_chegada[1] == aux->x.IATA_chegada[1] && IATA_chegada[2] == aux->x.IATA_chegada[2]) {
                
            /*Aloca memória e copia/calcula dados de voo*/
            ap_local = (ListaEscalas*)calloc(1, sizeof(ListaEscalas));

            ap_local->Voo1 = aux->x;                
            					
            ap_local->Total.hora_partida_total[0] = aux->x.hora_partida[0];
            ap_local->Total.hora_partida_total[1] = aux->x.hora_partida[1];
            ap_local->Total.hora_chegada_total[0] = aux->x.hora_chegada[0];
            ap_local->Total.hora_chegada_total[1] = aux->x.hora_chegada[1];
            ap_local->Total.tempo_total[0] = aux->x.tempo[0];
            ap_local->Total.tempo_total[1] = aux->x.tempo[1];
            ap_local->Total.distancia_total = aux->x.distancia;

            
            ap_local->prox = NULL;

            if (topo_escalas == NULL) {
                topo_escalas = ap_local;
                help=topo_escalas;
            } 
            else {
                help = topo_escalas;
                while (help->prox != NULL) {
                    help = help->prox;
                }
                help->prox = ap_local;
            }
        } 
    } 
    return topo_escalas;  
}

/*Cria voos com  1 escala*/
ListaEscalas* Adiciona_voo_1_escalas(ListaEscalas* topo_escalas, ListaRotas* topo_rotas, char IATA_partida[3], char IATA_chegada[3]){
    ListaRotas *aux1 = NULL, *aux2=NULL;
    ListaEscalas *ap_local = NULL, *help = NULL;
    float tempo_total;
   
    /*Passa por todos elementos da lista e verifica se o aeroporto de partida e o desejado e o de chegada nao*/
    for (aux1 = topo_rotas; aux1 != NULL; aux1=aux1->prox){
        if (IATA_partida[0] == aux1->x.IATA_partida[0] && IATA_partida[1] == aux1->x.IATA_partida[1] && IATA_partida[2] == aux1->x.IATA_partida[2]) {

            /*Passa novamente por todos elementos da lista e verifica se o aeroporto de chegada e o desejado, se o de partida e igual ao do chegada do encontrado no primeiro loop*/                
            for (aux2 = topo_rotas; aux2 != NULL; aux2=aux2->prox){
                if (IATA_chegada[0] == aux2->x.IATA_chegada[0] && IATA_chegada[1] == aux2->x.IATA_chegada[1] && IATA_chegada[2] == aux2->x.IATA_chegada[2] && aux1->x.IATA_chegada[0] == aux2->x.IATA_partida[0] && aux1->x.IATA_chegada[1] == aux2->x.IATA_partida[1] && aux1->x.IATA_chegada[2] == aux2->x.IATA_partida[2]){
                    

                    /*Aloca memoria e copia/calcula dados*/
                    ap_local = (ListaEscalas*)calloc(1, sizeof(ListaEscalas));


                    ap_local->Total.hora_partida_total[0] = aux1->x.hora_partida[0];
                    ap_local->Total.hora_partida_total[1] = aux1->x.hora_partida[1];
                    ap_local->Total.hora_chegada_total[0] = aux2->x.hora_chegada[0];
                    ap_local->Total.hora_chegada_total[1] = aux2->x.hora_chegada[1];

                    tempo_total = aux1->x.tempo_decimal +  aux2->x.tempo_decimal + (aux2->x.hora_universal_partida - aux1->x.hora_universal_chegada);
                    
                    ap_local->Total.tempo_total[0] = (int)(tempo_total);
                    ap_local->Total.tempo_total[1] = (tempo_total - (int)(tempo_total)) * 60;
                 

                    ap_local->Total.distancia_total = aux1->x.distancia + aux2->x.distancia;
                                      
                    ap_local->Voo1 = aux1->x;     
                    ap_local->Voo2 = aux2->x;            
                    					
                    ap_local->prox = NULL;

                    if (topo_escalas == NULL) {
                        topo_escalas = ap_local;
                        help=topo_escalas;
                    } 
                    else {
                        help = topo_escalas;
                        while (help->prox != NULL) {
                            help = help->prox;
                        }
                        help->prox = ap_local;
                    }  
                }
            }                       
        } 
    }  
    
    return topo_escalas;
}


/*Cria voo com 2 escalas*/
ListaEscalas* Adiciona_voo_2_escalas(ListaEscalas* topo_escalas, ListaRotas* topo_rotas, char IATA_partida[3], char IATA_chegada[3]){
    ListaRotas *aux1 = NULL, *aux2=NULL, *aux3=NULL;
    ListaEscalas *ap_local = NULL, *help = NULL;
    float tempo_total;
   
    /*Passa por todos elementos da lista e verifica se o aeroporto de partida e o desejado e o de chegada nao*/
    for (aux1 = topo_rotas; aux1 != NULL; aux1=aux1->prox){
        if (IATA_partida[0] == aux1->x.IATA_partida[0] && IATA_partida[1] == aux1->x.IATA_partida[1] && IATA_partida[2] == aux1->x.IATA_partida[2]) {
            
            /*Passa novamente por todos elementos da lista e verifica se o aeroporto de chegada nao e o desejado, se o de partida e igual ao do chegada do encontrado no primeiro loop*/  
            for (aux2 = topo_rotas; aux2 != NULL; aux2=aux2->prox){
                if (aux1->x.IATA_chegada[0] == aux2->x.IATA_partida[0] && aux1->x.IATA_chegada[1] == aux2->x.IATA_partida[1] && aux1->x.IATA_chegada[2] == aux2->x.IATA_partida[2] && aux1->x.hora_universal_chegada <= aux2->x.hora_universal_partida && IATA_chegada[0] != aux2->x.IATA_chegada[0] && IATA_chegada[1] != aux2->x.IATA_chegada[1] && IATA_chegada[2] != aux2->x.IATA_chegada[2] && aux2->x.IATA_chegada[0] != aux1->x.IATA_partida[0] && aux2->x.IATA_chegada[1] != aux1->x.IATA_partida[1] && aux2->x.IATA_chegada[2] != aux1->x.IATA_partida[2]){

                     /*Passa novamente por todos elementos da lista e verifica se o aeroporto de chegada e o desejado, se o de partida e igual ao do chegada do encontrado no segundo loop */
                    for (aux3 = topo_rotas; aux3 != NULL; aux3=aux3->prox){
                        if (IATA_chegada[0] == aux3->x.IATA_chegada[0] && IATA_chegada[1] == aux3->x.IATA_chegada[1] && IATA_chegada[2] == aux3->x.IATA_chegada[2] && aux2->x.IATA_chegada[0] == aux3->x.IATA_partida[0] && aux2->x.IATA_chegada[1] == aux3->x.IATA_partida[1] && aux2->x.IATA_chegada[2] == aux3->x.IATA_partida[2]){
                        
                            /*Aloca memoria e copia/calcula dados*/
                            ap_local = (ListaEscalas*)calloc(1, sizeof(ListaEscalas));

                            ap_local->Voo1 = aux1->x;     
                            ap_local->Voo2 = aux2->x;
                            ap_local->Voo3 = aux3->x;            
                            					
                            ap_local->Total.hora_partida_total[0] = aux1->x.hora_partida[0];
                            ap_local->Total.hora_partida_total[1] = aux1->x.hora_partida[1];
                            ap_local->Total.hora_chegada_total[0] = aux3->x.hora_chegada[0];
                            ap_local->Total.hora_chegada_total[1] = aux3->x.hora_chegada[1];
                            
                            tempo_total = aux1->x.tempo_decimal +  aux2->x.tempo_decimal + aux3->x.tempo_decimal + (aux2->x.hora_universal_partida - aux1->x.hora_universal_chegada) + (aux3->x.hora_universal_partida - aux2->x.hora_universal_chegada);
                            
                            ap_local->Total.tempo_total[0] = (int)(tempo_total);
                            ap_local->Total.tempo_total[1] = (tempo_total - (int)(tempo_total)) * 60;

                            ap_local->Total.distancia_total = aux1->x.distancia + aux2->x.distancia + aux3->x.distancia;
            
                            ap_local->prox = NULL;

                            if (topo_escalas == NULL) {
                                topo_escalas = ap_local;
                                help=topo_escalas;
                            } 
                            else {
                                help = topo_escalas;
                                while (help->prox != NULL) {
                                    help = help->prox;
                                }
                                help->prox = ap_local;
                            }                         
                        }
                    }
                }
            }                    
        } 
    }   
 
    return topo_escalas;
}
