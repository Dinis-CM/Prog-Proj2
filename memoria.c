#include "header.h"

/*Remove da lista um elemento e retorna o topo desta*/
ListaEscalas* RetiraDaLista(ListaEscalas** topo, ListaEscalas* ap_antes) {
    
    ListaEscalas *eliminar = NULL;

    if (*topo == NULL)
        return NULL;

    if (ap_antes == NULL) {
        eliminar = *topo;
        *topo = (*topo)->prox;
    } else {
        eliminar = ap_antes->prox;
        ap_antes->prox = eliminar->prox;
    }

    free(eliminar);
    return *topo;
}


/*Troca conteudos entre dois elementos da ListaEscalas*/
void troca_conteudos(ListaEscalas *a, ListaEscalas *b){

    DadosRotas temp;
    DadosEscalas aux;

    temp=a->Voo1;
    a->Voo1 = b->Voo1;
    b->Voo1=temp;

    temp=a->Voo2;
    a->Voo2 = b->Voo2;
    b->Voo2=temp;

    temp=a->Voo3;
    a->Voo3 = b->Voo3;
    b->Voo3=temp;

    aux=a->Total;
    a->Total = b->Total;
    b->Total=aux;
}

/*Limpa todos dados guardados na memória*/
void liberta_memoria(ListaAero* topo_aero, ListaRotas* topo_rotas, ListaEscalas* topo_escalas){

    ListaAero *aux_aero=NULL, *temp_aero=NULL;    
    ListaRotas *aux_rotas=NULL, *temp_rotas=NULL;
    ListaEscalas *aux_escalas=NULL, *temp_escalas=NULL;   
    
    for (aux_aero = topo_aero; aux_aero != NULL; aux_aero = temp_aero){
        temp_aero=aux_aero->prox;
        free(aux_aero); 
    }

    for (aux_rotas = topo_rotas; aux_rotas != NULL; aux_rotas = temp_rotas){
        temp_rotas=aux_rotas->prox;
        free(aux_rotas); 
    }
    
    for (aux_escalas = topo_escalas; aux_escalas != NULL; aux_escalas = temp_escalas){
        temp_escalas=aux_escalas->prox;
        free(aux_escalas); 
    }

    return;
}

/*Procura aeroporto na lista*/
ListaAero* procura_aeroporto(char IATA[3], ListaAero* *topo_aero){
    
    ListaAero *aux = NULL;    

/*Comparação do código IATA com os aeroportos da lista*/
    for (aux = *topo_aero; aux != NULL; aux = aux-> prox){     
        if(IATA[0] == aux->x.IATA[0] && IATA[1] == aux->x.IATA[1] && IATA[2] == aux->x.IATA[2])
            return aux;            
    } 

    return NULL;  
}    
