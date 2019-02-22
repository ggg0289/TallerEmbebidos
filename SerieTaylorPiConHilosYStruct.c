#include <stdio.h>
#include <math.h>
#include <pthread.h>

//Calcular 2arcsin(1), o sea pi, utilizando series de Taylor.

//Parámetros que se le pasarán a la función que ejecuten los hilos.
struct parametros
{
    int terminosTaylor; //Términos de la serie a utilizar.
    int hiloID;         //Identificador del hilo.
};

void *calcularPi(void *param); //Prototipo de la función para calcular pi.

int main(int argc, char *argv[])
{
    int numeroHilos;     //Contiene el número de hilos a crear.
    int nh;              //Contador para el número de hilos.

    printf("Calculo del valor de 2arcsin(1) (o sea, pi) utilizando series de Taylor. \n\n");

    printf("Ingrese el numero de hilos: ");
    scanf("%d", &numeroHilos);

    //Arreglos para parámetros relevantes con respecto al número de hilos.
    int unidadesDeTrabajo[numeroHilos];
    int terminosTaylor[numeroHilos];
    struct parametros P[numeroHilos]; //Parámetros para calcularPi.

    //Arreglos para variables de los hilos.
    pthread_t hiloID[numeroHilos]; //Identificador.
    int hiloRetorno[numeroHilos];  //Valor de retorno.

    printf("\nIngrese el numero de unidades de trabajo: \n");

    //Calcular los términos de la serie a partir de las unidades de trabajo para cada hilo.
    for (nh = 0; nh < numeroHilos; nh++)
    {
        printf("Hilo %d: ", nh+1);
        scanf("%d", &unidadesDeTrabajo[nh]);
        terminosTaylor[nh] = unidadesDeTrabajo[nh]*50;
    }

    printf("\nHilos trabajando: \n");

    //Asignación de parámetros.
    for (nh = 0; nh < numeroHilos; nh++)
    {
        P[nh].terminosTaylor = terminosTaylor[nh];
        P[nh].hiloID = nh+1;
    }

    //Creación de hilos.
    for (nh = 0; nh < numeroHilos; nh++)
    {
        hiloRetorno[nh] = pthread_create(&hiloID[nh], NULL, calcularPi, (void *)&P[nh]);
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
void *calcularPi(void *param)
{
    int n;                                  //Contador para el for.
    double valorTemporal;                   //Valor temporal durante el cálculo.
    double valorPi = 0;                     //Valor final de pi.
    //Parámetros a utilizar.
    struct parametros *p;
    p = (struct parametros *)param;

    //For para calcular el valor de pi.
    for(n = 0; n < p -> terminosTaylor; n++)
    {
        //valorTemporal = (6*pow(-1,n))/(((2*n)+1)*(pow(sqrt(3),((2*n)+1)))); //Cálculo del n-ésimo término. Converge rápido.
        valorTemporal = (4*pow(-1,n))/((2*n)+1);                              //Cálculo del n-ésimo término. Converge lento.
        valorPi = valorPi + valorTemporal;                                    //Cálculo del valor final de pi.
    }

    printf("\nHilo %d, %d terminos: 2arcsin(1) = %1.20lf \n",p -> hiloID, p -> terminosTaylor, valorPi);
}
