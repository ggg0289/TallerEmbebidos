#include <stdio.h>
#include <math.h>
#include <pthread.h>

//Calcular 2arcsin(1), o sea pi, utilizando series de Taylor.

void *calcularPi(void *tTaylor); //Prototipo de la función para calcular pi.

int main(int argc, char *argv[])
{
    int unidadesDeTrabajo;
    int *terminosTaylor;
    double valorPi;
    int numeroHilos;
    pthread_t hilo1;
    int a1;

    printf("Calculo del valor de 2arcsin(1) (o sea, pi) utilizando series de Taylor. \n\n");

    printf("Ingrese el numero de hilos: ");
    scanf("%d", &numeroHilos);

    printf("\nIngrese el numero de unidades de trabajo: ");
    scanf("%d", &unidadesDeTrabajo);

    terminosTaylor = unidadesDeTrabajo*50; //Calula los términos de la serie a partir de las unidades de trabajo.

    //Creacion de hilos.
    a1 = pthread_create(&hilo1, NULL, calcularPi, (void *)terminosTaylor);

    pthread_join(hilo1, NULL);

    printf("Fin del programa. \n");

    return 0;
}

//Función que calcula el valor de pi mediante series de Taylor.
void *calcularPi(void *tTaylor)
{
    int n;                //Contador para el for.
    double valorTemporal; //Valor temporal durante el cálculo.
    double valorPi = 0;   //Valor final de pi.
    int *terminosTaylor;
    terminosTaylor = (int *)tTaylor;

    for(n = 0; n < terminosTaylor; n++) //For para calcular el valor de pi.
    {
        valorTemporal = (6*pow(-1,n))/(((2*n)+1)*(pow(sqrt(3),((2*n)+1)))); //Cálculo del n-ésimo término.
        valorPi = valorPi + valorTemporal; //Cálculo del valor final de pi.
    }

    printf("\nEl valor de 2arcsin(1) es: %1.30lf \n\n", valorPi);
}
