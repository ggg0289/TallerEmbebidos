#include <pthread.h>
#include <semaphore.h>
//#include <stdio.h>
#include <unistd.h>
#include <curses.h>
#include <stdbool.h>

/*
Problema de los filósifos comiendo.
Cambios con respecto a 4_3: implementación en curses, arreglos a la funci[on de pausa/salir.
Basado en: https://www.geeksforgeeks.org/operating-system-dining-philosopher-problem-using-semaphores/
*/

#define NF 6                        //Número de filósofos.
#define PENSANDO 2                  //Estado de pensar.
#define HAMBRIENTO 1                //Estado de tener hambre.
#define COMIENDO 0                  //Estado de tener hambre.
#define IZQUIERDA (filID + 5) % NF  //Filósofo inmediatamente a la izquierda.
#define DERECHA (filID + 1) % NF    //Filósofo inmediatamente a la derecha.

int estado[NF];                             //Arreglo para el estado de cada filósofo.
int filosofos[NF] = { 0, 1, 2, 3, 4, 5 };   //Arreglo con la identificación de cada filósofo.

bool detener = false;   //Para salir del programa.
bool pausa = false;     //Para pausar el programa

sem_t mutex;            //Semáforo que actúa como mutex.
sem_t semFil[NF];       //Arreglo de semáforos para controlar a los filósofos.

//Funciones prototipo, se explican después del main.
void *acciones(void *filID);
void tomarPalillos(int filID);
void devolverPalillos(int filID);
void comer(int filID);
void *controlHilos();

int main()
{
    int i;          //Contador para los for.

    initscr();      //Iniciar curses. Se necesita para llamar a las funciones.
    noecho();       //No despliega lo que digite el teclado.
    curs_set(0);    //Ocultar el cursor.
    start_color();  //Para usar colores.

    //Parejas de colores a utilizar.
    init_pair(1,COLOR_RED,COLOR_BLACK);
    init_pair(2,COLOR_YELLOW,COLOR_BLACK);
    init_pair(3,COLOR_GREEN,COLOR_BLACK);
    init_pair(4,COLOR_BLUE,COLOR_BLACK);
    init_pair(5,COLOR_WHITE,COLOR_BLACK);

    //Imprimir paja.
    mvprintw(0, 0, "El Dilema De Los Filosofos:");
    mvprintw(2, 10, "\"El pensamiento lleva a la comida, la comida lleva al pensamiento.\"");
    mvprintw(4, 0, "Contemplad a los sabios y sus obras...");
    mvprintw(6, 0, "Filosofo     Palillo Izq.     Palillo Der.     Estado");
    for (i = 0; i < NF; i++)
    {
        attrset(COLOR_PAIR(5));
        mvprintw(7 + i, 3, "%d",i + 1);
        attrset(COLOR_PAIR(3));
        mvprintw(7 + i, 17, "%d                %d", i + 1, ((i + 1) % NF) + 1);
        refresh();
    }

    //Arreglos para variables de los hilos.
    pthread_t hiloID[NF+1];     //Identificador.
    int hiloRetorno[NF+1];      //Valor de retorno.

    sem_init(&mutex, 0, 1);     //Inicializar el mutex.

    //Inicializar los semáforos de los palillos.
    for (i = 0; i < NF; i++)
    {
        sem_init(&semFil[i], 0, 0);
    }

    //Creación del hilo de control.
    hiloRetorno[NF] = pthread_create(&hiloID[NF], NULL, controlHilos, NULL);

    //Creación de un hilo por filósofo.
    for (i = 0; i < NF; i++)
    {
        hiloRetorno[i] = pthread_create(&hiloID[i], NULL, acciones, (void *)&filosofos[i]);
        attrset(COLOR_PAIR(2));
        mvprintw(7 + i, 47, "Pensando  ");
        refresh();
        //printf("El filosofo %d esta pensando.\n", i + 1);
    }

    //Esperar para que todos los hilos terminen.
    for (i = 0; i < NF; i++){
        pthread_join(hiloID[i], NULL);
    }

    detener = true;

	//Esperar a que el hilo de control termine.
	pthread_join(hiloID[NF], NULL);

	attrset(COLOR_PAIR(4));
	mvprintw(14, 0, "Actividades concluidas. Presione una tecla para salir.");
    //printf("\n\nActividades concluidas. Presione una tecla para salir.\n");

    getch();    //Para que endwin no termine todo de una vez.
    endwin();   //Finaliza curses.
    return 0;
}

//Función para que los fil[osofos comiencen a actuar.
void *acciones(void *filID)
{
    while (1)
    {
        int *id = filID;        //Número de identificación del filósofo.
        usleep(100000);         ///Para visualización: afecta al tiempo de Pensando.
        tomarPalillos(*id);     //Tomar los palillos.
        //usleep(100000);         //No se necesita.
        devolverPalillos(*id);  //Devolver los palillos.

        //Para salir del programa.
        if(detener==true)
        {
            break;              //Sale del programa.
        }
    }
}

//Función para que un solo filósofo intente tomar los palillos.
void tomarPalillos(int filID)
{
    sem_wait(&mutex);   //Mutex lock.

    //Indicar que el filósofo tiene hambre.
    estado[filID] = HAMBRIENTO;
    attrset(COLOR_PAIR(3));
    mvprintw(7 + filID, 47, "Hambriento");
    refresh();
    //printf("El filosofo %d esta hambriento.\n", filID + 1);

    comer(filID);       //Intentar comer.
    sem_post(&mutex);   //Mutex unlock.

    //Si no puede comer, esperar.
    sem_wait(&semFil[filID]);
    usleep(100000);     ///Para visualización: afecta al tiempo de Hambriento/Comiendo.
}

//Función para que un solo filósofo intente devolver los palillos.
void devolverPalillos(int filID)
{
    sem_wait(&mutex);   //Mutex lock.

    //Indicar que el filósofo está pensando.
    estado[filID] = PENSANDO;
    attrset(COLOR_PAIR(3));
    mvprintw(7 + filID, 17, "%d                %d", filID + 1, DERECHA + 1);
    refresh();
    //printf("El filosofo %d esta devolviendo los palillos %d y %d.\n", filID + 1, filID + 1, DERECHA + 1);
    attrset(COLOR_PAIR(2));
    mvprintw(7 + filID, 47, "Pensando  ");
    refresh();
    //printf("El filosofo %d esta pensando.\n", filID + 1);

    //Si es posible, dejar que los vecinos inmediatos intenten comer.
    comer(IZQUIERDA);
    comer(DERECHA);

    sem_post(&mutex);   //Mutex unlock.
}

//Función para que el filósofo intente comer.
void comer(int filID)
{
    //El filósofo solo come si tiene hambre y sus vecinos inmediatos no están comiendo.
    if (estado[filID] == HAMBRIENTO && estado[IZQUIERDA] != COMIENDO && estado[DERECHA] != COMIENDO)
    {
        //Indicar que el filósofo está comiendo.
        estado[filID] = COMIENDO;
        usleep(100000);     ///Para visualización: afecta al tiempo de Hambriento.
        attrset(COLOR_PAIR(1));
        mvprintw(7 + filID, 17, "%d                %d", filID + 1, DERECHA + 1);
        refresh();
        //printf("El filosofo %d esta tomando los palillos %d y %d.\n", filID + 1, filID + 1, DERECHA +1);
        attrset(COLOR_PAIR(1));
        mvprintw(7 + filID, 47, "Comiendo  ");
        refresh();
        //printf("El filosofo %d esta comiendo.\n", filID + 1);

        //Sin efecto en tomarPalillos, aviso para los hambrientos en devolverPalillos.
        sem_post(&semFil[filID]);

        //Para pausar el programa.
        if (pausa==true)
        {
            while(pausa)
            {
                //Pausa el programa.
            }
        }
    }
}

//Función para pausar/detener el programa o salir de él.
void *controlHilos()
{
	while(!detener)
    {
        char var = 0;
        var = getch();

        if (var=='q')
        {
            detener=true;   //Si se teclea una q, se activa detener.
        }
        else
        {
            if (var=='p')
            {
                pausa=!pausa;   //Si se digita una p, se activa pausa.
            }
        }
	}
}
