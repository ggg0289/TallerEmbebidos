#include <stdio.h>
#include <math.h>
#include <curses.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

bool detener=false;
bool pausa = false;
int hilos=0;

typedef struct dato
{
	double unid,hilo;
	int y;
	bool detener_0, activo;
	} parametro;
void *serie(void *args)
{
	parametro *par=(parametro *)args;
	double pie=0;
	double picuartos=0;
	if(par->unid !=0){
		for(int i=0; i<=par->unid; i++){
			picuartos=picuartos+pow(-1,i)/(2*i+1);
			pie=4*picuartos;
			char *estado;

			fflush(stdout);
			printf("%c[%d;%df hilo %.f valor: %.50f ",0x1B, par->y,0, par->hilo, pie);
			int porc =(100*i)/par->unid;
			if(porc==100)
				par->activo=false;
			if(par->activo){
				estado="activo";
				}
			else
				estado="inactivo";			
			printf("%c[%d;%df el hilo esta %s lleva %i porciento de ejecucion ",0x1B, par->y+1,0, estado, porc);
			fflush(stdout);
			
			if(detener==true){
				break;}
			else if (pausa ==true){
				while(pausa){}}
		}
	}
}
void *lee_teclado(void *args)
{
	parametro *par=(parametro *)args;
	while(!detener){
		int i=par->unid;
		if(i!=0){
			char var=0;
			var = getchar();
			if (var=='q'){
			detener=true;
			}else if (var=='p'){
			pausa=!pausa;
			}
		}
	}
}
int main()
{	
	printf("Ingrese el numero de hilos: ");
	scanf("%d",&hilos);
	pthread_t hilo[hilos];
	parametro p[hilos];
	int pos_init=hilos+2;
	for(int i=0; i<hilos; i++){
		p[i].hilo=i+1;
		p[i].y=pos_init+i+1;
		p[i].activo=true;
		pos_init=pos_init+1;
		printf("Ingrese el numero de unidades del hilo %.f : ", p[i].hilo);
		scanf("%le",&p[i].unid);
		p[i].unid=p[i].unid*50;
		}
	
	pthread_create(&hilo[hilos], NULL, lee_teclado,(void *)&p[0]);
	
	for(int i=0; i<hilos; i++){
		pthread_create(&hilo[i], NULL, serie,(void *)&p[i]);		
		}
	
	for(int i=0; i<hilos; i++){
		pthread_join(hilo[i],NULL);
		}
	detener=true;
	pthread_join(hilo[hilos],NULL);
	

	return 0;
}

