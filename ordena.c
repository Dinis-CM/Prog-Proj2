#include "header.h"


void Ordena_lista(ListaEscalas* *topo, char arg[]) {
    
    if(strcmp(arg, "-TD")==0){
        Ordena_decrescente(topo);
    }

    else if(strcmp(arg, "-TC")==0){
        Ordena_crescente(topo);
    }

    else if(strcmp(arg, "-D")==0){
        Ordena_distancia(topo);
    }

    else{
        printf("Parâmetros inválidos \n");
        exit(1);    
    }   
}

void Ordena_crescente(ListaEscalas* *topo){
    
    int troca = 1;
    int i=0, j=0;

    ListaEscalas *atual=*topo;

    while(atual != NULL){
       atual = atual->prox;
       i++;
    }   

    while (troca == 1){

        troca = 0;
        atual=*topo;

        for (j = 0; j < i-1; j++){

            if (atual != NULL && atual->prox != NULL && (atual->Total.hora_partida_total[0] > atual->prox->Total.hora_partida_total[0] || (atual->Total.hora_partida_total[0] == atual->prox->Total.hora_partida_total[0] && atual->Total.hora_partida_total[1] > atual->prox->Total.hora_partida_total[1]))){
                troca_conteudos(atual, atual->prox);
                troca = 1;
            }

            atual=atual->prox;
        } 
            
    }
}

void Ordena_decrescente(ListaEscalas* *topo){
    
    int troca = 1;
    int i=0, j=0;

    ListaEscalas *atual=*topo;

    while(atual != NULL){
       atual = atual->prox;
       i++;
    }    
    
    while (troca == 1){
        
        troca = 0;
        atual=*topo;

        for (j = 0; j < i-1; j++){
            
             if (atual != NULL && atual->prox != NULL && (atual->Total.hora_partida_total[0] < atual->prox->Total.hora_partida_total[0] || (atual->Total.hora_partida_total[0] == atual->prox->Total.hora_partida_total[0] && atual->Total.hora_partida_total[1] < atual->prox->Total.hora_partida_total[1]))){
                troca_conteudos(atual, atual->prox);
                troca = 1;
            }
            atual=atual->prox;
        } 
            
    }
}

void Ordena_distancia(ListaEscalas** topo) {
    ListaEscalas *atual = *topo, *anterior = NULL, *temp = NULL;

    while (atual->prox != NULL) {
        temp = atual->prox;
        if (temp != NULL && atual->Total.distancia_total > temp->Total.distancia_total)
            atual = RetiraDaLista(topo, anterior);
        else {
            anterior = atual;
            atual = temp;
        }
    }

    if (anterior->prox!=NULL && anterior->Total.distancia_total < anterior->prox->Total.distancia_total)
        RetiraDaLista(topo, anterior);
}


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


