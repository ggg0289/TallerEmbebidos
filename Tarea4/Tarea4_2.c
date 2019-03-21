#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

//Problema de los fil�sifos comiendo.
//Cambios con respecto a 4_1: funci�n de pausa, error en los palillos, cambios para 6 fil�sofos.
//Basado en: https://www.geeksforgeeks.org/operating-system-dining-philosopher-problem-using-semaphores/

#define N 6                     //N�mero de fil�sofos.
#define THINKING 2              //Estado de pensar.
#define HUNGRY 1                //Estado de tener hambre.
#define EATING 0                //Estado de tener hambre.
#define LEFT (phnum + 5) % N    //Fil�sofo inmediatamente a la izquierda.
#define RIGHT (phnum + 1) % N   //Fil�sofo inmediatamente a la derecha.

int state[N];                           //Arreglo para el estado de cada fil�sofo.
int phil[N] = { 0, 1, 2, 3, 4, 5 };     //Arreglo con la identificaci�n de cada fil�sofo.

bool detener = false;   //Para detener el programa.
bool pausa = false;     //Para pausar el programa

sem_t mutex;    //Sem�foro que act�a como mutex.
sem_t S[N];     //Arreglo de sem�foros para controlar a los fil�sofos.

//Funciones prototipo, se explican despu�s del main.
void* philospher(void* num);
void take_fork(int phnum);
void put_fork(int phnum);
void test(int phnum);
void *controlHilos();

int main()
{
    int i;                  //Contador para los for.

    //Arreglos para variables de los hilos.
    pthread_t hiloID[N+1];  //Identificador.
    int hiloRetorno[N+1];   //Valor de retorno.

    sem_init(&mutex, 0, 1); //Inicializar el mutex.

    //Inicializar los sem�foros de los palillos.
    for (i = 0; i < N; i++)
    {
        sem_init(&S[i], 0, 0);
    }

    //Creaci�n del hilo de control.
    hiloRetorno[N] = pthread_create(&hiloID[N], NULL, controlHilos, NULL);

    //Creaci�n de un hilo por fil�sofo.
    for (i = 0; i < N; i++)
    {
        hiloRetorno[i] = pthread_create(&hiloID[i], NULL, philospher, (void *)&phil[i]);

        printf("Philosopher %d is thinking\n", i + 1);
    }

    //Esperar para que todos los hilos terminen.
    for (i = 0; i < N; i++){
        pthread_join(hiloID[i], NULL);
    }

    detener = true;
	//Esperar a que el hilo de control termine.
	pthread_join(hiloID[N], NULL);

    printf("\n\nActividades concluidas. Presione una tecla para salir. \n");
    return 0;
}

//Funci�n para tomar y devolver los palillos.
void* philospher(void* num)
{
    while (1)
    {
        int* i = num;   //N�mero de identificaci�n del fil�sofo.
        usleep(1);
        take_fork(*i);  //Tomar los palillos.
        usleep(0);
        put_fork(*i);   //Devolver los palillos.
    }
}

//Funci�n para que un solo fil�sofo intente tomar los palillos.
void take_fork(int phnum)
{
    sem_wait(&mutex);   //Mutex lock.

    //Indicar que el fil�sofo tiene hambre.
    state[phnum] = HUNGRY;
    printf("Philosopher %d is Hungry\n", phnum + 1);

    test(phnum);        //Intentar comer.
    sem_post(&mutex);   //Mutex unlock.

    //Si no puede comer, esperar.
    sem_wait(&S[phnum]);
    usleep(1);
}

//Funci�n para que un solo fil�sofo intente devolver los palillos.
void put_fork(int phnum)
{
    sem_wait(&mutex);   //Mutex lock.

    //Indicar que el fil�sofo est� pensando.
    state[phnum] = THINKING;
    printf("Philosopher %d putting fork %d and %d down\n", phnum + 1, phnum + 1, RIGHT +1);
    printf("Philosopher %d is thinking\n", phnum + 1);

    //Si es posible, dejar que los vecinos inmediatos intenten comer.
    test(LEFT);
    test(RIGHT);

    sem_post(&mutex);   //Mutex unlock.
}

//Funci�n para que el fil�sofo intente comer.
void test(int phnum)
{
    //El fil�sofo solo come si tiene hambre y sus vecinos inmediatos no est�n comiendo.
    if (state[phnum] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
    {
        //Indicar que el fil�sofo est� comiendo.
        state[phnum] = EATING;
        usleep(2);
        printf("Philosopher %d takes fork %d and %d\n", phnum + 1, phnum + 1, RIGHT +1);
        printf("Philosopher %d is Eating\n", phnum + 1);

        //Sin efecto en take_fork, aviso para los hambrientos en put_fork.
        sem_post(&S[phnum]);

        //Para pausar/detener el programa.
        /*if(detener==true)
        {
            break;  //Detiene el programa.
        }
        else
        {*/
            if (pausa==true)
            {
                while(pausa)
                {
                    //Pausa el programa.
                }
            }
        //}
    }
}

//Funci�n para pausar/detener el programa o salir de �l.
void *controlHilos()
{
	while(!detener)
    {
        char var = 0;
        var = getchar();

        if (var=='q')
        {
            detener=true;   //Si se teclea una q, se activa detener.
        }
        else
        {
            if (var=='p')
            {
                pausa=!pausa;   //Si se digita una p, se activa pausar.
            }
        }
	}
}
