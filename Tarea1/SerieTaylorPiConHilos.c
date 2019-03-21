#include <stdio.h>
#include <math.h>
#include <pthread.h>

//Calcular 2arcsin(1), o sea pi, utilizando series de Taylor.

void *calcularPi(void *tTaylor); //Prototipo de la función para calcular pi.

int main(int argc, char *argv[])
{
    int numeroHilos; //Numero de hilos a crear.
    int nh;          //Contador para el numero de nilos.

    printf("Calculo del valor de 2arcsin(1) (o sea, pi) utilizando series de Taylor. \n\n");

    printf("Ingrese el numero de hilos: ");
    scanf("%d", &numeroHilos);

    //Arreglos para unidades de trabajo y términos de la serie inicializados con el número de hilos.
    int unidadesDeTrabajo[numeroHilos];
    int *terminosTaylor[numeroHilos];

    //Arreglos para variables de los hilos.
    pthread_t hiloID[numeroHilos]; //Identificador.
    int hiloRetorno[numeroHilos];  //Valor de retorno.

    printf("\nIngrese el numero de unidades de trabajo: \n");

    //Calular los términos de la serie a partir de las unidades de trabajo para cada hilo.
    for (nh = 0; nh < numeroHilos; nh++)
    {
        printf("Hilo %d: ", nh+1);
        scanf("%d", &unidadesDeTrabajo[nh]);
        terminosTaylor[nh] = unidadesDeTrabajo[nh]*50;
    }

    printf("\nHilos trabajando: \n");

    //Creación de hilos.
    for (nh = 0; nh < numeroHilos; nh++)
    {
        hiloRetorno[nh] = pthread_create(&hiloID[nh], NULL, calcularPi, (void *)terminosTaylor[nh]);
    }

    //Esperar para que todos los hilos terminen.
    for (nh = 0; nh < numeroHilos; nh++)
    {
        pthread_join(hiloID[nh], NULL);
    }

    printf("\nFin del programa. \n");
    return 0;
}

//Función que calcula el valor de pi mediante series de Taylor.
void *calcularPi(void *tTaylor)
{
    int n;               //Contador para el for.
    double valorTemporal;//Valor temporal durante el cálculo.
    double valorPi = 0;  //Valor final de pi.
    //Número de terminos de la serie.
    int *terminosTaylor;
    terminosTaylor = (int *)tTaylor;

    //Calcular el valor de pi.
    for(n = 0; n < terminosTaylor; n++)
    {
        valorTemporal = (6*pow(-1,n))/(((2*n)+1)*(pow(sqrt(3),((2*n)+1)))); //Cálculo del n-ésimo término.
        valorPi = valorPi + valorTemporal;                                  //Cálculo del valor final de pi.
    }

    printf("Hilo : , TT: %d; 2arcsin(1) = %1.20lf \n", terminosTaylor, valorPi);
}
