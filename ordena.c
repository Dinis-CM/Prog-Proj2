#include "header.h"

//Decide o método de ordenação / selecao
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

//Ordena por ordem crescente
void Ordena_crescente(ListaEscalas* *topo){
    
    int troca = 1;
    int i=0, j=0;

    ListaEscalas *atual=*topo;

    //Numero de elementos na lista
    while(atual != NULL){
       atual = atual->prox;
       i++;
    }   

    //Passa pela lista i-1 vezes ou até nada trocar e troca conteudos se a hora de partida seguinte for menor
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

//Ordena por ordem crescente
void Ordena_decrescente(ListaEscalas* *topo){
    
    int troca = 1;
    int i=0, j=0;

    ListaEscalas *atual=*topo;

    //Numero de elementos na lista
    while(atual != NULL){
       atual = atual->prox;
       i++;
    }    
    
    //Passa pela lista i-1 vezes ou até nada trocar e troca conteudos se a hora de partida seguinte for menor
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

//Mostra apenas distancia mais curta
void Ordena_distancia(ListaEscalas** topo) {
    ListaEscalas *atual = *topo, *anterior = NULL, *temp = NULL;

    //Verifica se a lista tem dois ou mais elementos
    if(*topo==NULL || (*topo)->prox==NULL)
        return;

    //Se a distancia do elemento a seguir for menor, retira o elemento da lista
    while (atual->prox != NULL) {
        temp = atual->prox;
        if (temp != NULL && atual->Total.distancia_total > temp->Total.distancia_total)
            atual = RetiraDaLista(topo, anterior);
        else {
            anterior = atual;
            atual = temp;
        }
    }

    //Garantir que também se verifica o ultimo elemento da lista
    if (anterior->prox!=NULL && anterior->Total.distancia_total < anterior->prox->Total.distancia_total)
        RetiraDaLista(topo, anterior);
}


//Remove da lista um elemento e retorna o topo desta
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


//Troca conteudos entre dois elementos da ListaEscalas
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


