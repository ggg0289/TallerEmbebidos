#include <stdio.h>
#include <math.h>
#include <curses.h>
#include <pthread.h>

typedef struct dato
{
	char *cadena;
	int unid,hilo,x,y;
	} parametro;

void *serie(void *args)
{
	parametro *par=(parametro *)args;
	double pie;
	double picuartos=0;
	for(int i=0; i<=par->unid; i++){
		picuartos=picuartos+pow(-1,i)/(2*i+1);
		}
	pie=4*picuartos;
	printf("hilo %d valor: %1.50f \n", par->hilo, pie);
}
int main()
{
	printf("Hola mundo");
	
	int unidades=0;
	int hilos=0;
	printf("Ingrese las unidades de trabajo: ");
	scanf("%d",&unidades);
	printf("Ingrese el numero de hilos: ");
	scanf("%d",&hilos);
	
	pthread_t hilo[hilos];
	parametro p[hilos];
	
	for(int i=0; i<=hilos; i++){
		p[i].hilo=i;
		p[i].unid=unidades*50;
		}
	
	printf("El valor de pi con %d unidades y %d hilos se mostrara a continuacion: \n", unidades, hilos);
	
	for(int i=0; i<=hilos; i++){
		pthread_create(&hilo[i], NULL, serie,(void *)&p[0]);		
		}
	
	for(int i=0; i<=hilos; i++){
		pthread_join(hilo[i],NULL);
		}
		
	//pi=serie(unidades);
	
	
	return 0;
}
