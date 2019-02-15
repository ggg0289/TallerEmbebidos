#include <stdio.h>
#include <math.h>
#include <curses.h>
#include <pthread.h>

int main(){
	int unidades=0;
	int terminos=0;
	float pi=0;
	printf("Ingrese las unidades de trabajo: ");
	scanf("%d",&unidades);
	terminos=unidades*50;
	pi=serie(terminos);
	printf("El valor de pi con %d unidades de trabajor es: %d", unidades, pi);
	return 0;

int factorial(int a){
	int resultado=1;
	for(a; a>1; a--){
		resultado=resultado*a;
	}
	return resultado;

int serie(int n){
	float pimedios=0;
	float pi=0;
	for(int i=0; i<=n; i++){
		pimedios=pimedios+factorial(2*i)/(pow(4,i)*pow(factorial(i),2)*(2*i+1);
				}
	pi=2*pimedios;
	return pi;

