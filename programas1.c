#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct dato
{
	char *cadena;
	int x,y;
	} parametro;
	
void gotoxy(int x, int y){
		printf ("\033[%d;%df", y,x);
	}

void *saludo(void *args)
{
		parametro *par=(parametro *)args;
		int i;
		for (i=0; i< strlen(par->cadena); i++)
		{
			fflush(stdout);
			gotoxy(par->x, par->y);
			par->x++;
			printf("%c",par->cadena[i]);
			fflush(stdout);
			sleep(1);
		}
		printf("\n");
}

int main (int argc, char const *argv[])
{
	printf("Hola mundo \n");
	
	pthread_t hilo1[5];
	parametro p[5];
	p[0].cadena="hola";
	p[0].x=10;
	p[0].y=30;
	p[1].cadena="mundo";
	p[1].x=20;
	p[1].y=30;
	pthread_create(&hilo1[0], NULL, saludo, (void *)&p[0]);
	pthread_create(&hilo1[1], NULL, saludo, (void *)&p[1]);
	pthread_join(hilo1[0],NULL);
	pthread_join(hilo1[1],NULL);
	
	return 0;
}
