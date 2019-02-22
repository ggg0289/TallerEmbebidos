#include <stdio.h>
#include <math.h>

//Calcular 2arcsin(1), o sea pi, utilizando series de Taylor.

double calcularPi(int terminos); //Prototipo de la funci�n para calcular pi.

int main()
{
    int unidadesDeTrabajo;
    int terminosTaylor;
    double valorPi;

    printf("Calculo del valor de 2arcsin(1) (o sea, pi) utilizando series de Taylor. \n\n");
    printf("Ingrese el numero de unidades de trabajo: ");
    scanf("%d", &unidadesDeTrabajo);

    terminosTaylor = 50*unidadesDeTrabajo; //Calula los t�rminos de la serie a partir de las unidades de trabajo.
    valorPi = calcularPi(terminosTaylor); //Llama a la funci�n que calcula el valor de pi.

    printf("El valor de 2arcsin(1) es: %1.20lf \n\n", valorPi);
    printf("Fin del programa. \n");

    return 0;
}

//Funci�n que calcula el valor de pi mediante series de Taylor.
double calcularPi(int terminos)
{
    int n;                     //Contador para el for.
    double valorTemporal; //Valor temporal durante el c�lculo.
    double valorPi = 0;       //Valor final de pi.

    for(n = 0; n < terminos; n++) //For para calcular el valor de pi.
    {
        valorTemporal = (6*pow(-1,n))/(((2*n)+1)*(pow(sqrt(3),((2*n)+1)))); //C�lculo del n-�simo t�rmino.
        printf("temporal %1.20lf \n\n", valorTemporal);
        valorPi = valorPi + valorTemporal; //C�lculo del valor final de pi.
        printf("pi %1.20lf \n\n", valorPi);
    }

    return valorPi; //Retorna el valor final de pi.
}
