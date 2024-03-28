#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void leitura(char filename[], ListaAero* *topo_aero, ListaRotas* *topo_rotas, ListaAero* *ap_reg_anterior_aero, ListaRotas* *ap_reg_anterior_rotas){

    FILE *fp;
        
    fp = fopen(filename, "r");  

    if (fp == NULL){
        printf("Erro na abertura do ficheiro %s .\n", filename);
        exit(1);
    }
    
    if(strcmp(filename, "aeroportos.txt")==0){
        leitura_lista_aero(fp, topo_aero, ap_reg_anterior_aero);
    }
    
    else if(strcmp(filename, "rotas.txt")==0){
       leitura_lista_rotas(fp, topo_rotas, ap_reg_anterior_rotas, topo_aero);
    }
    
    fclose(fp); 

}

void leitura_lista_aero(FILE *fp, ListaAero* *topo_aero, ListaAero* *ap_reg_anterior_aero){
    
    ListaAero* ap_local = NULL;
    ListaAero *aux = *topo_aero;   
    
    char line[200];
    int lat[3], lon[3], tz, count, k;
    char IATA[3], ICAO[4], slat, slon, cidade[40], resto[10];
 
    while(fgets(line, 200, fp)){    

        count = sscanf(line, "%c%c%c%c %c%c%c %d %d %d %c %d %d %d %c %s %d %s", &ICAO[0], &ICAO[1], &ICAO[2], &ICAO[3], &IATA[0], &IATA[1], &IATA[2], &lat[0], &lat[1], &lat[2], &slat, &lon[0], &lon[1], &lon[2], &slon, cidade, &tz, resto);

        if (count == 17 && 'A'<=ICAO[0]<='Z' && 'A'<=ICAO[1]<='Z' && 'A'<=ICAO[2]<='Z' && 'A'<=ICAO[3]<='Z' && 'A'<=IATA[0]<='Z' && 'A'<=IATA[1]<='Z' && 'A'<=IATA[2]<='Z' && 0<=lat[0]<=180 && 0<=lat[1]<=60 && 0<=lat[2]<=60 && 0<=lon[0]<=180 && 0<=lon[1]<=60 && 0<=lon[2]<=60 && -12<=tz<=12 && (slat=='N' || slat=='S') && (slon=='W' || slon=='E')) {
            
            ap_local = (ListaAero*)calloc(1, sizeof(ListaAero));

            if (ap_local == NULL) {
                printf("Falta de memoria durante a insercao\n");
                exit(2);
            }

            for(k=0; k<3; k++)
                ap_local->x.IATA[k] = IATA[k];


            for(k=0; k<4; k++)
                ap_local->x.ICAO[k] = ICAO[k];

            for(k=0; k<3; k++)
                ap_local->x.lat[k] = lat[k];
            
            for(k=0; k<3; k++)
                ap_local->x.lon[k] = lon[k];
        
            strcpy(ap_local->x.cidade,cidade);


            ap_local->x.slat = slat;
            ap_local->x.slon = slon;
            ap_local->x.tz = tz;
            ap_local->prox = NULL;

            if (*topo_aero == NULL) {
                *topo_aero = ap_local;
                aux = *topo_aero;
            } 
            else {
                aux = *topo_aero;
                while (aux->prox != NULL) {
                    aux = aux->prox;
                }
                aux->prox = ap_local;
            }
        }
    }
}

void leitura_lista_rotas(FILE *fp, ListaRotas* *topo_rotas, ListaRotas* *ap_reg_anterior_rotas, ListaAero* *topo_aero){
    
    ListaRotas* ap_local = NULL;
    ListaRotas *aux = *topo_rotas;  
    
    char line[200];

    int hora_partida[2], hora_chegada[2], tempo[2], count1, count2, k;
    float distancia, tempo_decimal;
    char companhia[30], codigo[10], IATA_partida[3], IATA_chegada[3], resto[10];
 
    while(fgets(line, 200, fp)){    

        count1 = sscanf(line, "AIRLINE : %s %s", companhia, resto);
        count2 = sscanf(line, "%s %c%c%c %d:%d %c%c%c %d:%d %s", codigo, &IATA_partida[0], &IATA_partida[1], &IATA_partida[2], &hora_partida[0], &hora_partida[1], &IATA_chegada[0], &IATA_chegada[1], &IATA_chegada[2], &hora_chegada[0], &hora_chegada[1], resto);
        
       
        
        if (count2 == 11 && 'A'<=IATA_partida[0]<='Z' && 'A'<=IATA_partida[1]<='Z' && 'A'<=IATA_partida[2]<='Z' && 'A'<=IATA_chegada[0]<='Z' && 'A'<=IATA_chegada[1]<='Z' && 'A'<=IATA_chegada[2]<='Z' && 0<=hora_partida[0]<=23 && 0<=hora_partida[1]<=59 && 0<=hora_chegada[0]<=23 && 0<=hora_chegada[1]<=59) {
            
			distancia = calcula_distancia(IATA_partida, IATA_chegada, topo_aero);
        	tempo_decimal = calcula_tempo(IATA_partida, IATA_chegada, hora_partida, hora_chegada, topo_aero);
        	tempo[0] = (int)tempo_decimal; 
        	tempo[1] = (int)((tempo_decimal - tempo[0]) * 60);
			
           

			if(distancia>0 && tempo_decimal>0){
				
				ap_local = (ListaRotas*)calloc(1, sizeof(ListaRotas));
				if (ap_local == NULL) {
                printf("Falta de memoria durante a insercao\n");
                exit(2);
            	}

            	strcpy(ap_local->x.companhia, companhia);
	            strcpy(ap_local->x.codigo, codigo);
	            for(k=0; k<3; k++)
	                ap_local->x.IATA_partida[k] = IATA_partida[k];
	            for(k=0; k<4; k++)
	                ap_local->x.IATA_chegada[k] = IATA_chegada[k];
	            ap_local->x.hora_partida[0] = hora_partida[0];
	            ap_local->x.hora_partida[1] = hora_partida[1];
	            ap_local->x.hora_chegada[0] = hora_chegada[0];
	            ap_local->x.hora_chegada[1] = hora_chegada[1];
	            ap_local->x.tempo[0] = tempo[0];
	            ap_local->x.tempo[1] = tempo[1];
	            ap_local->x.distancia = distancia;
	
	            ap_local->prox = NULL;
	
	            if (*topo_rotas == NULL) {
	                *topo_rotas = ap_local;
	                aux = *topo_rotas;
	            } 
	            else {
	                aux = *topo_rotas;
	                while (aux->prox != NULL) {
	                    aux = aux->prox;
	                }
	                aux->prox = ap_local;
	            }

			}
        }
    }
}


void Mostra_lista_aero(ListaAero* topo) {

    ListaAero *aux, *temp;

    if (topo == NULL) {
        printf("\n--- Lista esta vazia --- \n");
        return;
    }
    
    for (aux = topo; aux != NULL; aux = temp){
        printf("%c%c%c%c %c%c%c %d %d %d %c %d %d %d %c  %s %d \n", aux->x.ICAO[0], aux->x.ICAO[1], aux->x.ICAO[2], aux->x.ICAO[3], aux->x.IATA[0], aux->x.IATA[1], aux->x.IATA[2], aux->x.lat[0], aux->x.lat[1], aux->x.lat[2], aux->x.slat, aux->x.lon[0], aux->x.lon[1], aux->x.lon[2], aux->x.slon, aux->x.cidade, aux->x.tz);
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
    printf("%s %s %c%c%c %02d:%02d %c%c%c %02d:%02d %d  %02d:%02d \n", aux->x.companhia, aux->x.codigo, aux->x.IATA_partida[0], aux->x.IATA_partida[1], aux->x.IATA_partida[2], aux->x.hora_partida[0], aux->x.hora_partida[1], aux->x.IATA_chegada[0], aux->x.IATA_chegada[1], aux->x.IATA_chegada[2], aux->x.hora_chegada[0], aux->x.hora_chegada[1], aux->x.distancia, aux->x.tempo[0], aux->x.tempo[1]);   
    temp=aux->prox;
    free(aux);   
    }
}

 
float calcula_distancia(char partida[3], char chegada[3], ListaAero* *topo){
    
    ListaAero *aux = NULL;    
    ListaAero *xpartida = NULL;
    ListaAero *xchegada = NULL;

    float latp=0, lonp=0, latc=0, lonc=0, xp=0, yp=0, zp=0, xc=0, yc=0, zc=0, theta=0, distancia=-99999;    
    
    for (aux = *topo; aux != NULL; aux = aux-> prox){
        
        if(partida[0]==aux->x.IATA[0] && partida[1]==aux->x.IATA[1] && partida[2]==aux->x.IATA[2])            
            xpartida = aux;      

        if(chegada[0]==aux->x.IATA[0] && chegada[1]==aux->x.IATA[1] && chegada[2]==aux->x.IATA[2])            
            xchegada = aux;     
    }    
       
	if(xpartida!=NULL && xchegada!=NULL){
        converte_distancia_decimal(xchegada, latc, lonc, &xc, &yc, &zc);
        converte_distancia_decimal(xpartida, latp, lonp, &xp, &yp, &zp);
        
        theta = acos(((xc*xp)+(yc*yp)+(zc*zp))/(sqrt(xc*xc+yc*yc+zc*zc) * sqrt(xp*xp+yp*yp+zp*zp)));
        
        if(theta>(PI/2)){
            theta =  PI - theta; 
        }

        distancia = 6381 * sin(theta); 
    }  
    return distancia;     
} 

void converte_distancia_decimal(ListaAero *aux, float lat, float lon, float *x, float *y, float *z){
    if(aux->x.slat=='N'){
        lat = aux->x.lat[0] + (aux->x.lat[1] / 60.0) + (aux->x.lat[2] / 3600.0);
    }    
    else if(aux->x.slat=='S'){
        lat = -(aux->x.lat[0] + (aux->x.lat[1] / 60.0) + (aux->x.lat[2] / 3600.0));
    }  
    
    if(aux->x.slon=='E'){
        lon = aux->x.lon[0] + (aux->x.lon[1] / 60.0) + (aux->x.lon[2] / 3600.0);
    }    
    else if(aux->x.slon=='W'){
        lon = -(aux->x.lon[0] + (aux->x.lon[1] / 60.0) + (aux->x.lon[2] / 3600.0));
    } 

    *x = 6381 * cos(PI/180 * lat) * cos(PI/180 * lon);
    *y = 6381 * cos(PI/180 * lat) * sin(PI/180 * lon);
    *z = 6381 * sin (PI/180 * lat);

}

float calcula_tempo(char partida[3], char chegada[3], int hora_partida[2], int hora_chegada[2], ListaAero* *topo_aero){
    
    ListaAero *aux = NULL; 
    ListaAero *ap_partida = NULL;
    ListaAero *ap_chegada = NULL;    

    float tempo=0, tzp, tzc, hc, hp;    
    
    for (aux = *topo_aero; aux != NULL; aux = aux->prox){
		if(partida[0]==aux->x.IATA[0] && partida[1]==aux->x.IATA[1] && partida[2]==aux->x.IATA[2]){
            ap_partida = aux;
        }           
		if(chegada[0]==aux->x.IATA[0] && chegada[1]==aux->x.IATA[1] && chegada[2]==aux->x.IATA[2]){
            ap_chegada = aux;
        }            
    }  

    if(ap_partida!=NULL && ap_chegada!=NULL){
        hp = hora_partida[0] + (hora_partida[1] / 60.0) - ap_partida->x.tz;
        hc = hora_chegada[0] + (hora_chegada[1] / 60.0) - ap_chegada->x.tz;
        tempo = hc- hp;
    }
    
    return tempo;    
} 

void Seleciona_lista(ListaRotas* *topo, ListaRotas *ap_reg_antes, char IATA_partida[3], char IATA_chegada[3], char escala[1]){

    ListaRotas *aux = NULL, *ap_antes=NULL;

    int n_escala=-1, count=0;

	count=sscanf(escala, "%d", &n_escala); 
 
    if(n_escala==0){
        for (aux = *topo; aux != NULL; ){
            if (IATA_partida[0] != aux->x.IATA_partida[0] || IATA_partida[1] != aux->x.IATA_partida[1] || IATA_partida[2] != aux->x.IATA_partida[2] || IATA_chegada[0] != aux->x.IATA_chegada[0] || IATA_chegada[1] != aux->x.IATA_chegada[1] || IATA_chegada[2] != aux->x.IATA_chegada[2]) {
				*topo = RetiraDaLista(topo, ap_antes);
				aux = *topo;
			} 
			else{
				ap_antes = aux; 
				aux = aux->prox; 
			}          
		}		       
    }
}

ListaRotas* RetiraDaLista(ListaRotas* *topo, ListaRotas* ap_antes) {
    
	ListaRotas *eliminar=NULL;

	if (*topo == NULL)
		return *topo;

	if (ap_antes == NULL) {
		eliminar = *topo;
		*topo = (*topo)->prox;
	}
	else {
	eliminar = ap_antes->prox;
	ap_antes->prox = eliminar->prox;
	}

	free(eliminar);
	return *topo;
}

void Ordena_lista(ListaRotas *topo, char arg[]) {
    
    if(strcmp(arg, "-TD")==0){
        Ordena_decrescente(&topo);
    }

    if(strcmp(arg, "-TC")==0){
        Ordena_crescente(&topo);
    }

    
}

void Ordena_crescente(ListaRotas* *topo){
    int troca = 1;
    int i=0, j=0;

    ListaRotas *atual=*topo;

    while(atual != NULL){
 
       atual = atual->prox;
       i++;
    }   
    
    while (troca == 1)
    {
        troca = 0; // Supor que é a última vez
        atual=*topo;
        for (j = 0; j < i-1; j++){
            if (atual != NULL && atual->prox != NULL && (atual->x.hora_partida[0] > atual->prox->x.hora_partida[0] ||(atual->x.hora_partida[0] == atual->prox->x.hora_partida[0] && atual->x.hora_partida[1] > atual->prox->x.hora_partida[1])))
            {
                troca_conteudos(atual, atual->prox);
                troca = 1;
            }
            atual=atual->prox;
        } 
            
    }
}

void Ordena_decrescente(ListaRotas* *topo){
    int troca = 1;
    int i=0, j=0;

    ListaRotas *atual=*topo;

    while(atual != NULL){
 
       atual = atual->prox;
       i++;
    }    
    
    while (troca == 1)
    {
        troca = 0; // Supor que é a última vez
        atual=*topo;
        for (j = 0; j < i-1; j++){
            if (atual != NULL && atual->prox != NULL && (atual->x.hora_partida[0] < atual->prox->x.hora_partida[0] ||(atual->x.hora_partida[0] == atual->prox->x.hora_partida[0] && atual->x.hora_partida[1] < atual->prox->x.hora_partida[1])))
            {
                troca_conteudos(atual, atual->prox);
                troca = 1;
            }
            atual=atual->prox;
        } 
            
    }
}

void troca_conteudos(ListaRotas *a, ListaRotas *b){
    DadosRotas temp;
    temp=a->x;
    a->x = b->x;
    b->x=temp;
}





