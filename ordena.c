#include "header.h"

/*Decide o método de ordenação / selecao*/
int Ordena_lista(ListaEscalas* *topo, char arg[], int n_escala) {

    if(*topo == NULL)
        return 0;
    
    if(strcmp(arg, "-TD")==0){
        Ordena_decrescente(topo, n_escala);
    }

    else if(strcmp(arg, "-TC")==0){
        Ordena_crescente(topo, n_escala);
    }

    else if(strcmp(arg, "-D")==0){
        Ordena_distancia(topo, n_escala);
    }

    else{
        printf("Parâmetros inválidos \n");
        return 1;
    } 
    return 0;  
}

/*Ordena por ordem crescente*/
void Ordena_crescente(ListaEscalas* *topo, int n_escala){
    
    int troca = 1;
    int i=0, j=0;

    ListaEscalas *atual=*topo;
    ListaEscalas *anterior = NULL;
    ListaEscalas *temp = NULL;

    /*Se a hora de partida do voo a seguir for menor do que o chegada do anterior, retira o elemento da lista*/
    while (atual->prox != NULL) {
        temp = atual->prox;
        if (n_escala==1 && (atual->Voo1.hora_universal_chegada > atual->Voo2.hora_universal_partida))
            atual = RetiraDaLista(topo, anterior);
        else if (n_escala==2 && (atual->Voo1.hora_universal_chegada > atual->Voo2.hora_universal_partida || atual->Voo2.hora_universal_chegada > atual->Voo3.hora_universal_partida))
            atual = RetiraDaLista(topo, anterior);
        else {
            anterior = atual;
            atual = temp;
        }
    }

    /*Garantir que também se verifica o ultimo elemento da lista*/
    if (n_escala==1 && (atual->Voo1.hora_universal_chegada > atual->Voo2.hora_universal_partida))
        atual = RetiraDaLista(topo, anterior);
    else if (n_escala==2 && (atual->Voo1.hora_universal_chegada > atual->Voo2.hora_universal_partida || atual->Voo2.hora_universal_chegada > atual->Voo3.hora_universal_partida))
        atual = RetiraDaLista(topo, anterior);

    /*Procura numero de elementos na lista filtrada*/
    for(atual = *topo; atual != NULL; atual=atual->prox)
       i++;

    /*Passa pela lista i-1 vezes ou até nada trocar e troca conteudos se a hora de partida seguinte for menor*/
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

/*Ordena por ordem decrescente*/
void Ordena_decrescente(ListaEscalas* *topo, int n_escala){
    
    int troca = 1;
    int i=0, j=0;

    ListaEscalas *atual=*topo;
    ListaEscalas *anterior = NULL;
    ListaEscalas *temp = NULL;

    /*Se a hora de partida do voo a seguir for menor do que o chegada do anterior, retira o elemento da lista*/
    while (atual->prox != NULL) {
        temp = atual->prox;
        if (n_escala==1 && (atual->Voo1.hora_universal_chegada > atual->Voo2.hora_universal_partida))
            atual = RetiraDaLista(topo, anterior);
        else if (n_escala==2 && (atual->Voo1.hora_universal_chegada > atual->Voo2.hora_universal_partida || atual->Voo2.hora_universal_chegada > atual->Voo3.hora_universal_partida))
            atual = RetiraDaLista(topo, anterior);
        else {
            anterior = atual;
            atual = temp;
        }
    }

    /*Garantir que também se verifica o ultimo elemento da lista*/
    if (n_escala==1 && (atual->Voo1.hora_universal_chegada > atual->Voo2.hora_universal_partida))
        atual = RetiraDaLista(topo, anterior);
    else if (n_escala==2 && (atual->Voo1.hora_universal_chegada > atual->Voo2.hora_universal_partida || atual->Voo2.hora_universal_chegada > atual->Voo3.hora_universal_partida))
        atual = RetiraDaLista(topo, anterior);

    /*Procura numero de elementos na lista filtrada*/
    for(atual = *topo; atual != NULL; atual=atual->prox)
       i++;

    /*Passa pela lista i-1 vezes ou até nada trocar e troca conteudos se a hora de partida seguinte for menor*/
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

/*Mostra apenas distancia mais curta*/
void Ordena_distancia(ListaEscalas** topo, int n_escala) {

    ListaEscalas *atual = *topo, *anterior = NULL, *temp = NULL;

    /*Verifica se a lista tem dois ou mais elementos ou se sao so voos diretos*/
    if(*topo==NULL || (*topo)->prox==NULL || n_escala == 0)
        return;

    /*Se a distancia do elemento a seguir for menor, retira o elemento da lista*/
    while (atual->prox != NULL) {
        temp = atual->prox;
        if (temp != NULL && atual->Total.distancia_total > temp->Total.distancia_total)
            atual = RetiraDaLista(topo, anterior);
        else {
            anterior = atual;
            atual = temp;
        }
    }

    /*Garantir que também se verifica o ultimo elemento da lista*/
    if (anterior->prox!=NULL && anterior->Total.distancia_total < anterior->prox->Total.distancia_total)
        RetiraDaLista(topo, anterior);
}



