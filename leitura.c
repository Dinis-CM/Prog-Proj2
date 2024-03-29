#include "header.h"

void leitura(char filename[], ListaAero* *topo_aero, ListaRotas* *topo_rotas){

    FILE *fp;
        
    fp = fopen(filename, "r");  

    if (fp == NULL){
        printf("Erro na abertura do ficheiro %s .\n", filename);
        exit(1);
    }
    
    if(strcmp(filename, "aeroportos.txt")==0)
        leitura_lista_aero(fp, topo_aero);
    
    else if(strcmp(filename, "rotas.txt")==0)
       leitura_lista_rotas(fp, topo_rotas, topo_aero);
    
    fclose(fp); 

}

void leitura_lista_aero(FILE *fp, ListaAero* *topo_aero){
    
    ListaAero *ap_local = NULL;
    ListaAero *aux = *topo_aero;   
  
    int lat[3], lon[3], tz, count, k;
    char line[200], IATA[3], ICAO[4], slat, slon, cidade[40], resto[10];
 
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
        
            strcpy(ap_local->x.cidade, cidade);

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

                while (aux->prox != NULL)
                    aux = aux->prox;

                aux->prox = ap_local;
            }
        }
    }
}

void leitura_lista_rotas(FILE *fp, ListaRotas* *topo_rotas, ListaAero* *topo_aero){
    
    ListaRotas *ap_local = NULL;
    ListaRotas *aux = *topo_rotas;  
    
    int hora_partida[2], hora_chegada[2], tempo[2], count1, count2, k;
    float distancia, tempo_decimal=-99, hora_universal_partida, hora_universal_chegada;
    char line[200], companhia[80], companhia1[30], companhia2[30], codigo[10], IATA_partida[3], IATA_chegada[3], resto[10];
 
    while(fgets(line, 200, fp)){    

        count1 = sscanf(line, "AIRLINE : %s %s", companhia1, companhia2);
        
        if(count1 == 2)
            strcpy(companhia, strcat(companhia1, companhia2));
        else if(count1 == 1)
            strcpy(companhia, companhia1);

        count2 = sscanf(line, "%s %c%c%c %d:%d %c%c%c %d:%d %s", codigo, &IATA_partida[0], &IATA_partida[1], &IATA_partida[2], &hora_partida[0], &hora_partida[1], &IATA_chegada[0], &IATA_chegada[1], &IATA_chegada[2], &hora_chegada[0], &hora_chegada[1], resto);
            
        if (count2 == 11 && 'A'<=IATA_partida[0]<='Z' && 'A'<=IATA_partida[1]<='Z' && 'A'<=IATA_partida[2]<='Z' && 'A'<=IATA_chegada[0]<='Z' && 'A'<=IATA_chegada[1]<='Z' && 'A'<=IATA_chegada[2]<='Z' && 0<=hora_partida[0]<=23 && 0<=hora_partida[1]<=59 && 0<=hora_chegada[0]<=23 && 0<=hora_chegada[1]<=59) {
            
			distancia = calcula_distancia(IATA_partida, IATA_chegada, topo_aero);

        	calcula_tempo(IATA_partida, IATA_chegada, hora_partida, hora_chegada, &tempo_decimal, &hora_universal_partida, &hora_universal_chegada, topo_aero);

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
                ap_local->x.hora_universal_partida = hora_universal_partida;
                ap_local->x.hora_universal_chegada = hora_universal_chegada;
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

	                while (aux->prox != NULL)
	                    aux = aux->prox;
	            
	                aux->prox = ap_local;
	            }

			}
        }
    }
}


