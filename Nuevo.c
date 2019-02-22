#include <stdio.h>
#include <math.h>
#include <curses.h>
#include <pthread.h>


double serie(int n){
	double pi=0;
	double picuartos=0;
	n=n*50;
	for(int i=0; i<=n; i++){
		
		picuartos=picuartos+pow(-1,i)/(2*i+1);
				
		}
	pi=4*picuartos;
	return pi;
}
int main()
{
	printf("Hola mundo");
	
	int unidades=0;
	double pi=0;
	printf("Ingrese las unidades de trabajo: ");
	scanf("%d",&unidades);
	pi=serie(unidades);
	printf("El valor de pi con %d unidades de trabajor es: %f \n", unidades, pi);
	
	return 0;
}
