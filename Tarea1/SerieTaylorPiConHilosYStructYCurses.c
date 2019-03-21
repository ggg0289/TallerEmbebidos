#include <math.h>
#include <stdlib.h>
#include <pthread.h>
#include <curses.h>
#include <stdbool.h>

//Calcular 2arcsin(1), o sea pi, utilizando series de Taylor.

int numeroHilos;        //Contiene el n�mero de hilos a crear.
bool detener = false;
bool pausa = false;

//Par�metros que se le pasar�n a la funci�n que ejecuten los hilos.
typedef struct parametros
{
    int terminosTaylor;     //T�rminos de la serie a utilizar.
    int hiloID;             //Identificador del hilo.
    bool activo;            //Hilo activo/true o inactivo/false.
} parametros;

void *calcularPi(void *param);    //Prototipo de la funci�n para calcular pi.
void *controlHilos(void *param); //Prototipo de la funci�n para pausar/salir del programa.

int main(int argc, char *argv[])
{
    int nh;              //Contador para el n�mero de hilos.
    char NH[2];          //El n�mero de hilos se obtiene como un string, se guarda aqu� para convertirlo despu�s.

    initscr();           //Iniciar curses. Se necesita para llamar a las funciones.

    mvprintw(0, 0, "Calculo del valor de pi utilizando series de Taylor.");
    //printf("Calculo del valor de 2arcsin(1) (o sea, pi) utilizando series de Taylor. \n\n");

    mvprintw(2, 0, "Ingrese el numero de hilos: ");
    getnstr(NH,2);
    numeroHilos = atoi(NH);
    //printf("Ingrese el numero de hilos: ");
    //mvscanw(2, 28, "%d", &numeroHilos);   //Esta funci�n no sirvi�, se cae la progra.
    //numeroHilos = getch()-48;             //Captura inmediatamente un caracter, pero le mete m�gicamente un offset de 48.
    //mvprintw(3, 0, "%d", numeroHilos);    //Des-comentar para verificar si se ingres� bien el dato.
    //scanf("%d", &numeroHilos);

    int unidadesDeTrabajo[numeroHilos];     //Almacenar las unidades de trabajo.
    parametros P[numeroHilos];              //Par�metros para calcularPi.

    //Arreglos para variables de los hilos.
    pthread_t hiloID[numeroHilos+1];        //Identificador.
    int hiloRetorno[numeroHilos+1];         //Valor de retorno.

    mvprintw(4, 0, "Ingrese el numero de unidades de trabajo: ");
    //printf("\nIngrese el numero de unidades de trabajo: \n");

    //Calcular los t�rminos de la serie a partir de las unidades de trabajo para cada hilo.
    for (nh = 0; nh < numeroHilos; nh++)
    {
        mvprintw(5+nh, 0, "Hilo %d: ", nh+1);
        //printf("Hilo %d: ", nh+1);
        mvscanw(5+nh, 8, "%d", &unidadesDeTrabajo[nh]);
        //scanf("%d", &unidadesDeTrabajo[nh]);
        //Asignaci�n de par�metros.
        P[nh].terminosTaylor = unidadesDeTrabajo[nh]*50;
        P[nh].hiloID = nh+1;
        P[nh].activo = true;
    }

    mvprintw(7+numeroHilos, 0, "Hilos trabajando...");
    //printf("\nHilos trabajando:");

    mvprintw(8+numeroHilos, 0, "Hilo     Porcentaje     Valor De Pi     Estado");

    //Creaci�n del hilo de control.
    hiloRetorno[numeroHilos] = pthread_create(&hiloID[numeroHilos], NULL, controlHilos, (void *)&P[numeroHilos]);

    //Creaci�n de hilos de trabajo.
    for (nh = 0; nh < numeroHilos; nh++)
    {
        hiloRetorno[nh] = pthread_create(&hiloID[numeroHilos], NULL, calcularPi, (void *)&P[nh]);
    }

    //Esperar para que todos los hilos terminen.
    for (nh = 0; nh < numeroHilos; nh++)
    {
        pthread_join(hiloID[nh], NULL);
    }

	detener = true;
	//Esperar a que el hilo de control termine.
	pthread_join(hiloID[numeroHilos], NULL);

    mvprintw(11+2*numeroHilos, 0, "Calculos concluidos. Presione una tecla para salir.");
    //printf("\n\nFin del programa. \n");

    getch();    //Para que endwin no termine todo de una vez.
    endwin();   //Finaliza curses.
    return 0;
}

//Funci�n que calcula el valor de pi mediante series de Taylor.
void *calcularPi(void *param)
{
    int n;                  //Contador para el for.
    int porcentaje;         //Porcentaje de tarea completada.
    double valorTemporal;   //Valor temporal durante el c�lculo.
    double valorPi = 0;     //Valor final de pi.
    char *estado;           //Estado del hilo, activo/inactivo.
    //Par�metros a utilizar.
    parametros *p = (parametros *)param;

    //For para calcular el valor de pi.
    for(n = 0; n <= p->terminosTaylor; n++)
    {
        //valorTemporal = (6*pow(-1,n))/(((2*n)+1)*(pow(sqrt(3),((2*n)+1)))); //C�lculo del n-�simo t�rmino. Converge r�pido.
        valorTemporal = (4*pow(-1,n))/((2*n)+1);                              //C�lculo del n-�simo t�rmino. Converge lento.
        valorPi = valorPi + valorTemporal;                                    //C�lculo del valor final de pi.
        porcentaje = (100*n)/(p->terminosTaylor);

        if(porcentaje==100)
            p->activo=false;

        if(p->activo)
        {
            estado = "Activo";
        }
        else
        {
            estado = "Inactivo";
        }

        mvprintw(8 + numeroHilos + p->hiloID, 0, "%d        %d             %.10f    %s", p->hiloID, porcentaje, valorPi, estado);
        move(8 + numeroHilos + p->hiloID, 0);
        refresh();
        //printf("\nHilo %d, %d terminos: 2arcsin(1) = %1.20lf",p -> hiloID, p -> terminosTaylor, valorPi);

        if(detener==true)
        {
            break;
        }
        else
        {
            if (pausa==true)
            {
                while(pausa)
                {
                }
            }
        }
    }
}

void *controlHilos(void *param)
{
	parametros *p = (parametros *)param;

	while(!detener)
    {
		int i = p->terminosTaylor;
		if(i!=0)
		{
			char var = 0;
			var = getch();

			if (var=='q')
            {
                detener=true;
			}
            else
            {
			    if (var=='p')
                {
                    pausa=!pausa;
                }
			}
		}
	}
}
