#include "header.h"

void Mostra_lista_aero(ListaAero* topo) {

    ListaAero *aux, *temp;

    if (topo == NULL) {
        printf("\n--- Lista esta vazia --- \n");
        return;
    }
    
    for (aux = topo; aux != NULL; aux = temp){
        
        printf("\n---Aeroporto de %s------------------------------------------------------------------------------------ \n", aux->x.cidade);
        printf("Codigo ICAO: %c%c%c%c  Codigo IATA: %c%c%c  Coordenadas: %d %d %d %c %d %d %d %c  Hora local: %d \n", aux->x.ICAO[0], aux->x.ICAO[1], aux->x.ICAO[2], aux->x.ICAO[3], aux->x.IATA[0], aux->x.IATA[1], aux->x.IATA[2], aux->x.lat[0], aux->x.lat[1], aux->x.lat[2], aux->x.slat, aux->x.lon[0], aux->x.lon[1], aux->x.lon[2], aux->x.slon, aux->x.tz);
        printf("-------------------------------------------------------------------------------------------------------\n");   
       
        temp = aux->prox;
        free(aux);
    }
}

void Mostra_lista_rotas(ListaRotas* topo) {

    ListaRotas *aux, *temp;

    if (topo == NULL) {
        printf("\n--- Lista esta vazia --- \n");
        return;
    }
    
    
    for (aux = topo; aux != NULL; aux = temp){ 
    
        printf("\n---Voo de %c%c%c a %c%c%c------------------------------------------------------------------------------------ \n", aux->x.IATA_partida[0], aux->x.IATA_partida[1], aux->x.IATA_partida[2],  aux->x.IATA_chegada[0], aux->x.IATA_chegada[1], aux->x.IATA_chegada[2]);
        printf("Companhia: %s  Codigo: %s  Hora de partida (local): %02d:%02d  Hora de chegada (local): %02d:%02d Tempo: %02d:%02d  Distancia: %d km \n", aux->x.companhia, aux->x.codigo, aux->x.hora_partida[0], aux->x.hora_partida[1], aux->x.hora_chegada[0], aux->x.hora_chegada[1], aux->x.tempo[0], aux->x.tempo[1], aux->x.distancia);
        printf("-------------------------------------------------------------------------------------------------------\n");   
    
        temp=aux->prox;
        free(aux);   
    }
}

void Mostra_lista_escalas(ListaEscalas* topo, char escala[1]) {

    int n_escala=-1;

    sscanf(escala, "%d", &n_escala); 

    if (topo == NULL) {
        printf("\n--- Lista esta vazia --- \n");
        return;
    }
    
    if(n_escala==0)
        Mostra_lista_0_escalas(topo);    
    if(n_escala==1)
        Mostra_lista_1_escalas(topo);   
    if(n_escala==2)
        Mostra_lista_2_escalas(topo); 
     
}


void Mostra_lista_0_escalas(ListaEscalas* topo){

    ListaEscalas *aux, *temp;
    
    for (aux = topo; aux != NULL; aux = temp){        
        printf("\n---Voo de %c%c%c a %c%c%c------------------------------------------------------------------------------------ \n", aux->Voo1.IATA_partida[0], aux->Voo1.IATA_partida[1], aux->Voo1.IATA_partida[2],  aux->Voo1.IATA_chegada[0], aux->Voo1.IATA_chegada[1], aux->Voo1.IATA_chegada[2]);
        printf("Companhia: %s  Codigo: %s  Hora de partida (local): %02d:%02d  Hora de chegada (local): %02d:%02d Tempo: %02d:%02d  Distancia: %d km \n", aux->Voo1.companhia, aux->Voo1.codigo, aux->Voo1.hora_partida[0], aux->Voo1.hora_partida[1], aux->Voo1.hora_chegada[0], aux->Voo1.hora_chegada[1], aux->Voo1.tempo[0], aux->Voo1.tempo[1], aux->Voo1.distancia);
        printf("-------------------------------------------------------------------------------------------------------\n");   
     
    temp=aux->prox;
    free(aux); 
    }
}

void Mostra_lista_1_escalas(ListaEscalas* topo){

    ListaEscalas *aux, *temp;
    
    for (aux = topo; aux != NULL; aux = temp){        
        printf("\n---Voo de %c%c%c a %c%c%c------------------------------------------------------------------------------------ \n", aux->Voo1.IATA_partida[0], aux->Voo1.IATA_partida[1], aux->Voo1.IATA_partida[2],  aux->Voo2.IATA_chegada[0], aux->Voo2.IATA_chegada[1], aux->Voo2.IATA_chegada[2]);
        printf("Voo 1 - Companhia: %s  Codigo: %s  Hora de partida (local): %02d:%02d  Hora de chegada (local): %02d:%02d Tempo: %02d:%02d  Distancia: %d km \n", aux->Voo1.companhia, aux->Voo1.codigo, aux->Voo1.hora_partida[0], aux->Voo1.hora_partida[1], aux->Voo1.hora_chegada[0], aux->Voo1.hora_chegada[1], aux->Voo1.tempo[0], aux->Voo1.tempo[1], aux->Voo1.distancia);
        printf("Voo 2 - Companhia: %s  Codigo: %s  Hora de partida (local): %02d:%02d  Hora de chegada (local): %02d:%02d Tempo: %02d:%02d  Distancia: %d km \n", aux->Voo2.companhia, aux->Voo2.codigo, aux->Voo2.hora_partida[0], aux->Voo2.hora_partida[1], aux->Voo2.hora_chegada[0], aux->Voo2.hora_chegada[1], aux->Voo2.tempo[0], aux->Voo2.tempo[1], aux->Voo2.distancia);
        printf("Hora de partida (local): %02d:%02d  Hora de chegada (local): %02d:%02d Tempo total: %02d:%02d  Distancia total: %d km\n", aux->Total.hora_partida_total[0], aux->Total.hora_partida_total[1], aux->Total.hora_chegada_total[0], aux->Total.hora_chegada_total[1], aux->Total.tempo_total[0], aux->Total.tempo_total[1], aux->Total.distancia_total);
        printf("-------------------------------------------------------------------------------------------------------\n");   
     
    temp=aux->prox;
    free(aux); 
    }
}
void Mostra_lista_2_escalas(ListaEscalas* topo){
    
    ListaEscalas *aux, *temp;
    
    for (aux = topo; aux != NULL; aux = temp){        
        printf("\n---Voo de %c%c%c a %c%c%c------------------------------------------------------------------------------------ \n", aux->Voo1.IATA_partida[0], aux->Voo1.IATA_partida[1], aux->Voo1.IATA_partida[2],  aux->Voo3.IATA_chegada[0], aux->Voo3.IATA_chegada[1], aux->Voo3.IATA_chegada[2]);
        printf("Voo 1 - Companhia: %s  Codigo: %s  Hora de partida (local): %02d:%02d  Hora de chegada (local): %02d:%02d Tempo: %02d:%02d  Distancia: %d km \n", aux->Voo1.companhia, aux->Voo1.codigo, aux->Voo1.hora_partida[0], aux->Voo1.hora_partida[1], aux->Voo1.hora_chegada[0], aux->Voo1.hora_chegada[1], aux->Voo1.tempo[0], aux->Voo1.tempo[1], aux->Voo1.distancia);
        printf("Voo 2 - Companhia: %s  Codigo: %s  Hora de partida (local): %02d:%02d  Hora de chegada (local): %02d:%02d Tempo: %02d:%02d  Distancia: %d km \n", aux->Voo2.companhia, aux->Voo2.codigo, aux->Voo2.hora_partida[0], aux->Voo2.hora_partida[1], aux->Voo2.hora_chegada[0], aux->Voo2.hora_chegada[1], aux->Voo2.tempo[0], aux->Voo2.tempo[1], aux->Voo2.distancia);
        printf("Voo 3 - Companhia: %s  Codigo: %s  Hora de partida (local): %02d:%02d  Hora de chegada (local): %02d:%02d Tempo: %02d:%02d  Distancia: %d km \n", aux->Voo3.companhia, aux->Voo3.codigo, aux->Voo3.hora_partida[0], aux->Voo3.hora_partida[1], aux->Voo3.hora_chegada[0], aux->Voo3.hora_chegada[1], aux->Voo3.tempo[0], aux->Voo3.tempo[1], aux->Voo3.distancia);
        printf("Hora de partida (local): %02d:%02d  Hora de chegada (local): %02d:%02d Tempo total: %02d:%02d  Distancia total: %d km\n", aux->Total.hora_partida_total[0], aux->Total.hora_partida_total[1], aux->Total.hora_chegada_total[0], aux->Total.hora_chegada_total[1], aux->Total.tempo_total[0], aux->Total.tempo_total[1], aux->Total.distancia_total);
        printf("-------------------------------------------------------------------------------------------------------\n");   
     
    temp=aux->prox;
    free(aux); 
    }
}