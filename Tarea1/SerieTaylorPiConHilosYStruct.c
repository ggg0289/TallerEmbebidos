#include <stdio.h>
#include <math.h>
#include <pthread.h>

//Calcular 2arcsin(1), o sea pi, utilizando series de Taylor.

//Par�metros que se le pasar�n a la funci�n que ejecuten los hilos.
struct parametros
{
    int terminosTaylor; //T�rminos de la serie a utilizar.
    int hiloID;         //Identificador del hilo.
};

void *calcularPi(void *param); //Prototipo de la funci�n para calcular pi.

int main(int argc, char *argv[])
{
    int numeroHilos;     //Contiene el n�mero de hilos a crear.
    int nh;              //Contador para el n�mero de hilos.

    printf("Calculo del valor de 2arcsin(1) (o sea, pi) utilizando series de Taylor. \n\n");

    printf("Ingrese el numero de hilos: ");
    scanf("%d", &numeroHilos);

    int unidadesDeTrabajo[numeroHilos];//Almacenar las unidades de trabajo.
    struct parametros P[numeroHilos];  //Par�metros para calcularPi.

    //Arreglos para variables de los hilos.
    pthread_t hiloID[numeroHilos]; //Identificador.
    int hiloRetorno[numeroHilos];  //Valor de retorno.

    printf("\nIngrese el numero de unidades de trabajo: \n");

    //Calcular los t�rminos de la serie a partir de las unidades de trabajo para cada hilo.
    for (nh = 0; nh < numeroHilos; nh++)
    {
        printf("Hilo %d: ", nh+1);
        scanf("%d", &unidadesDeTrabajo[nh]);
        //Asignaci�n de par�metros.
        P[nh].terminosTaylor = unidadesDeTrabajo[nh]*50;
        P[nh].hiloID = nh+1;
    }

    printf("\nHilos trabajando:");

    //Creaci�n de hilos.
    for (nh = 0; nh < numeroHilos; nh++)
    {
        hiloRetorno[nh] = pthread_create(&hiloID[nh], NULL, calcularPi, (void *)&P[nh]);
    }

    //Esperar para que todos los hilos terminen.
    for (nh = 0; nh < numeroHilos; nh++)
    {
        pthread_join(hiloID[nh], NULL);
    }

    printf("\n\nFin del programa. \n");
    return 0;
}

//Funci�n que calcula el valor de pi mediante series de Taylor.
void *calcularPi(void *param)
{
    int n;                                  //Contador para el for.
    double valorTemporal;                   //Valor temporal durante el c�lculo.
    double valorPi = 0;                     //Valor final de pi.
    //Par�metros a utilizar.
    struct parametros *p;
    p = (struct parametros *)param;

    //For para calcular el valor de pi.
    for(n = 0; n < p -> terminosTaylor; n++)
    {
        //valorTemporal = (6*pow(-1,n))/(((2*n)+1)*(pow(sqrt(3),((2*n)+1)))); //C�lculo del n-�simo t�rmino. Converge r�pido.
        valorTemporal = (4*pow(-1,n))/((2*n)+1);                              //C�lculo del n-�simo t�rmino. Converge lento.
        valorPi = valorPi + valorTemporal;                                    //C�lculo del valor final de pi.
    }

    printf("\nHilo %d, %d terminos: 2arcsin(1) = %1.20lf",p -> hiloID, p -> terminosTaylor, valorPi);
}
