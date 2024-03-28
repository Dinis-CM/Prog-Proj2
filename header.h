#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.14159265359

typedef struct DadosRotas{
    int hora_partida[2], hora_chegada[2], distancia, tempo[2];
    char companhia[30], codigo[10], IATA_partida[3], IATA_chegada[3];
}DadosRotas;

typedef struct ListaRotas {
    DadosRotas x;
    struct ListaRotas *prox;
}ListaRotas;

typedef struct DadosAero{
    char IATA[3], ICAO[4],  cidade[40], slat, slon;
    int lat[3], lon[3], tz;
}DadosAero;

typedef struct ListaAero {
    DadosAero x;
    struct ListaAero *prox;
}ListaAero;

void leitura(char filename[], ListaAero* *topo_aero, ListaRotas* *topo_rotas, ListaAero* *ap_reg_anterior_aero, ListaRotas* *ap_reg_anterior_rotas);

void leitura_lista_aero(FILE *fp, ListaAero* *topo_aero, ListaAero* *ap_reg_anterior_aero);

void leitura_lista_rotas(FILE *fp, ListaRotas* *topo_rotas, ListaRotas* *ap_reg_anterior_rotas, ListaAero* *topo_aero);

void Mostra_lista_aero(ListaAero* topo); 

void Mostra_lista_rotas(ListaRotas* topo);

float calcula_distancia(char partida[3], char chegada[3], ListaAero* *topo_aero);

float calcula_tempo(char partida[3], char chegada[3], int Hora_partida[2], int hora_chegada[2], ListaAero* *topo_aero);

void converte_distancia_decimal(ListaAero *aux, float lat, float lon, float* x, float *y, float *z);

void Seleciona_lista(ListaRotas* *topo, ListaRotas *ap_antes, char IATA_partida[3], char IATA_chegada[3], char escala[1]);

ListaRotas* RetiraDaLista(ListaRotas* *topo, ListaRotas* ap_antes);

void Ordena_lista(ListaRotas *topo, char arg[]);

void Ordena_decrescente(ListaRotas **topo);

void Ordena_crescente(ListaRotas **topo);

void troca_conteudos(ListaRotas *a, ListaRotas *b);

