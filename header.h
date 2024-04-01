#ifndef HEADER
#define HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.14159265359

/*Estruturas*/

/*Estrutura que guarda os dados das rotas*/
typedef struct DadosRotas{
    int hora_partida[2], hora_chegada[2], distancia, tempo[2];
    char companhia[30], codigo[10], IATA_partida[3], IATA_chegada[3];
    float hora_universal_partida, hora_universal_chegada, tempo_decimal;
}DadosRotas;

/*Lista das diversas rotas*/
typedef struct ListaRotas {
    DadosRotas x;
    struct ListaRotas *prox;
}ListaRotas;

/*Estrutura que guarda os dados dos aeroportos*/
typedef struct DadosAero{
    char IATA[3], ICAO[4],  cidade[40], slat, slon;
    int lat[3], lon[3], tz;
}DadosAero;

/*Lista dos diversos aeroportos*/
typedef struct ListaAero {
    DadosAero x;
    struct ListaAero *prox;
}ListaAero;

/*Estrutura que guarda os dados gerais dos voos com escalas*/
typedef struct DadosEscalas{
    int tempo_total[2], hora_partida_total[2], hora_chegada_total[2], distancia_total; 
    char IATA_partida_total[3], IATA_chegada_total[3]; 
}DadosEscalas;

/*Lista dos diversos voos com escalas*/
typedef struct ListaEscalas {
    DadosRotas Voo1;
    DadosRotas Voo2;
    DadosRotas Voo3;
    DadosEscalas Total;
    struct ListaEscalas *prox;
}ListaEscalas;


/*Funcoes*/

/*Leitura.c*/
void leitura(char filename[], ListaAero* *topo_aero, ListaRotas* *topo_rotas);
void leitura_lista_aero(FILE *fp, ListaAero* *topo_aero);
void leitura_lista_rotas(FILE *fp, ListaRotas* *topo_rotas, ListaAero* *topo_aero);

/*Calculo.c*/
float calcula_distancia(char partida[3], char chegada[3], ListaAero* *topo_aero);
float calcula_tempo(char partida[3], char chegada[3], int hora_partida[2], int hora_chegada[2], float* hp, float*hc, ListaAero* *topo_aero);
void converte_distancia_decimal(ListaAero *aux, float lat, float lon, float* x, float *y, float *z);

/*Mostra.c*/
void Mostra_lista_aero(ListaAero* topo);
void Mostra_lista_rotas(ListaRotas *topo);
void Mostra_lista_escalas(ListaEscalas* topo, int n_escala);

/*Seleciona.c*/
ListaEscalas* Seleciona_lista(ListaRotas* topo_rotas, char IATA_partida[3], char IATA_chegada[3], int n_escala);
ListaEscalas* Adiciona_voo_0_escalas(ListaEscalas* topo_escalas, ListaRotas* topo_rotas, char IATA_partida[3], char IATA_chegada[3]);
ListaEscalas* Adiciona_voo_1_escalas(ListaEscalas* topo_escalas, ListaRotas* topo_rotas, char IATA_partida[3], char IATA_chegada[3]);
ListaEscalas* Adiciona_voo_2_escalas(ListaEscalas* topo_escalas, ListaRotas* topo_rotas, char IATA_partida[3], char IATA_chegada[3]);

/*Ordena.c*/
void Ordena_lista(ListaEscalas* *topo, char arg[], int n_escala);
void Ordena_decrescente(ListaEscalas **topo, int n_escala);
void Ordena_crescente(ListaEscalas* *topo, int n_escala);
void Ordena_distancia(ListaEscalas* *topo, int n_escala);

/*Memoria.c*/
void troca_conteudos(ListaEscalas *a, ListaEscalas *b);
ListaEscalas* RetiraDaLista(ListaEscalas* *topo, ListaEscalas* ap_antes);
void liberta_memoria(ListaAero* topo_aero, ListaRotas* topo_rotas, ListaEscalas* topo_escalas);

#endif
