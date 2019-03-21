#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

//Problema de los filósifos comiendo.
//Cambios con respecto al original: comentarios en el código.
//Basado en: https://www.geeksforgeeks.org/operating-system-dining-philosopher-problem-using-semaphores/

#define N 5                     //Número de filósofos.
#define THINKING 2              //Estado de pensar.
#define HUNGRY 1                //Estado de tener hambre.
#define EATING 0                //Estado de tener hambre.
#define LEFT (phnum + 4) % N    //Filósofo inmediatamente a la izquierda.
#define RIGHT (phnum + 1) % N   //Filósofo inmediatamente a la derecha.

int state[N];                   //Arreglo para el estado de cada filósofo.
int phil[N] = { 0, 1, 2, 3, 4 };//Arreglo con la identificación de cada filósofo.

sem_t mutex;                    //Semáforo que actúa como mutex.
sem_t S[N];                     //Arreglo de semáforos para controlar a los filósofos.

//Funciones prototipo, se explican después del main.
void* philospher(void* num);
void take_fork(int phnum);
void put_fork(int phnum);
void test(int phnum);

int main()
{
    int i;                  //Contador para los for.

    //Arreglos para variables de los hilos.
    pthread_t hiloID[N];    //Identificador.
    int hiloRetorno[N];     //Valor de retorno.

    sem_init(&mutex, 0, 1); //Inicializar el mutex.

    //Inicializar los semáforos de los palillos.
    for (i = 0; i < N; i++)
    {
        sem_init(&S[i], 0, 0);
    }

    //Creación de un hilo por filósofo.
    for (i = 0; i < N; i++)
    {
        hiloRetorno[i] = pthread_create(&hiloID[i], NULL, philospher, (void *)&phil[i]);

        printf("Philosopher %d is thinking\n", i + 1);
    }

    //Esperar para que todos los hilos terminen.
    for (i = 0; i < N; i++){
        pthread_join(hiloID[i], NULL);
    }

    printf("\n\nActividades concluidas. Presione una tecla para salir. \n");
    return 0;
}

//Función para tomar y devolver los palillos.
void* philospher(void* num)
{
    while (1)
    {
        int* i = num;   //Número de identificación del filósofo.
        usleep(10);
        take_fork(*i);  //Tomar los palillos.
        usleep(10);
        put_fork(*i);   //Devolver los palillos.
    }
}

//Función para que un solo filósofo intente tomar los palillos.
void take_fork(int phnum)
{
    sem_wait(&mutex);   //Mutex lock.

    //Indicar que el filósofo tiene hambre.
    state[phnum] = HUNGRY;
    printf("Philosopher %d is Hungry\n", phnum + 1);

    test(phnum);        //Intentar comer.
    sem_post(&mutex);   //Mutex unlock.

    //Si no puede comer, esperar.
    sem_wait(&S[phnum]);
    usleep(10);
}

//Función para que un solo filósofo intente devolver los palillos.
void put_fork(int phnum)
{
    sem_wait(&mutex);   //Mutex lock.

    //Indicar que el filósofo está pensando.
    state[phnum] = THINKING;
    printf("Philosopher %d putting fork %d and %d down\n", phnum + 1, LEFT + 1, phnum + 1);
    printf("Philosopher %d is thinking\n", phnum + 1);

    //Si es posible, dejar que los vecinos inmediatos intenten comer.
    test(LEFT);
    test(RIGHT);

    sem_post(&mutex);   //Mutex unlock.
}

//Función para que el filósofo intente comer.
void test(int phnum)
{
    //El filósofo solo come si tiene hambre y sus vecinos inmediatos no están comiendo.
    if (state[phnum] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
    {
        //Indicar que el filósofo está comiendo.
        state[phnum] = EATING;
        usleep(20);
        printf("Philosopher %d takes fork %d and %d\n", phnum + 1, LEFT + 1, phnum + 1);
        printf("Philosopher %d is Eating\n", phnum + 1);

        //Sin efecto en take_fork, aviso para los hambrientos en put_fork.
        sem_post(&S[phnum]);
    }
}
