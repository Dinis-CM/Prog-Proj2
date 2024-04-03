#include "header.h"


/*Calculo distancia entre dois aeroportos*/
float calcula_distancia(ListaAero *xpartida, ListaAero *xchegada){   

    float latp=0, lonp=0, latc=0, lonc=0, xp=0, yp=0, zp=0, xc=0, yc=0, zc=0, theta=0, distancia=-99999;    

    /*Se os aeroportos de partida e chegada forem encontrados, calcular usando grande círculo*/
	if(xpartida!=NULL && xchegada!=NULL){
        
        converte_distancia_decimal(xchegada, latc, lonc, &xc, &yc, &zc);
        converte_distancia_decimal(xpartida, latp, lonp, &xp, &yp, &zp);
        

        theta = acos(((xc*xp)+(yc*yp)+(zc*zp))/(sqrt(xc*xc+yc*yc+zc*zc) * sqrt(xp*xp+yp*yp+zp*zp)));
        
        if(theta>(PI/2))
            theta =  PI - theta; 

        distancia = 6381 * sin(theta); 
    } 
 
    return distancia;     
} 

/*Converte a latitude e longitude do aeroporto (graus, minutos e segundos) para coordenas cartesianas*/
void converte_distancia_decimal(ListaAero *aux, float lat, float lon, float *x, float *y, float *z){

    if(aux->x.slat=='N')
        lat = aux->x.lat[0] + (aux->x.lat[1] / 60.0) + (aux->x.lat[2] / 3600.0);
 
    else if(aux->x.slat=='S')
        lat = -(aux->x.lat[0] + (aux->x.lat[1] / 60.0) + (aux->x.lat[2] / 3600.0)); 
    
    if(aux->x.slon=='E')
        lon = aux->x.lon[0] + (aux->x.lon[1] / 60.0) + (aux->x.lon[2] / 3600.0);
   
    else if(aux->x.slon=='W')
        lon = -(aux->x.lon[0] + (aux->x.lon[1] / 60.0) + (aux->x.lon[2] / 3600.0));

    *x = 6381 * cos(PI/180 * lat) * cos(PI/180 * lon);
    *y = 6381 * cos(PI/180 * lat) * sin(PI/180 * lon);
    *z = 6381 * sin (PI/180 * lat);

}

/*Cálculo do tempo decimal desde a descolagem até à aterragem*/
float calcula_tempo(int hora_partida[2], int hora_chegada[2], float* hp, float*hc, ListaAero* xpartida, ListaAero* xchegada){
    
    float tempo;  
    
	/*Se os aeroportos de partida e chegada forem encontrados, calcular tempo decimal*/
    if(xpartida!=NULL && xchegada!=NULL){
        *hp = hora_partida[0] + (hora_partida[1] / 60.0) - xpartida->x.tz;
        *hc = hora_chegada[0] + (hora_chegada[1] / 60.0) - xchegada->x.tz;
        tempo = *hc - *hp;
        if (tempo<0)
            tempo = 24 + tempo;
    } 
    return tempo;
} 

