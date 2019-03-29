#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h> 

#define N 6 
#define THINKING 2 
#define HUNGRY 1 
#define EATING 0 
#define LEFT (phnum + 4) % N 
#define RIGHT (phnum + 1) % N 

int state[N]; 
int phil[N] = { 0, 1, 2, 3, 4 }; 

sem_t mutex; 
sem_t S[N]; 

void test(int phnum) 
{ 
	if (state[phnum] == HUNGRY 
		&& state[LEFT] != EATING 
		&& state[RIGHT] != EATING) { 
		// state that eating 
		state[phnum] = EATING; 

		sleep(2); 

		printf("Filósofo %d toma palillo %d y %d\n", 
					phnum + 1, LEFT + 1, phnum + 1); 

		printf("Filósofo %d está comiendo\n", phnum + 1); 

		// sem_post(&S[phnum]) no tiene efecto 
		// mientras se toma el palillo 
		// usado para despertar al filósofo hambriento 
		// durante la toma de palillos 
		sem_post(&S[phnum]); 
	} 
} 

// Tomando palillo 
void take_fork(int phnum) 
{ 

	sem_wait(&mutex); 

	// Estado Habriento 
	state[phnum] = HUNGRY; 

	printf("Filósofo %d está hambriento\n", phnum + 1); 

	// Come si sus vecinos no estan comiendo 
	test(phnum); 

	sem_post(&mutex); 

	// si está habilitado para comer espera la señal 
	sem_wait(&S[phnum]); 

	sleep(1); 
} 

// Deja de usar los palillos 
void put_fork(int phnum) 
{ 

	sem_wait(&mutex); 

	// Estado Pensando 
	state[phnum] = THINKING; 

	printf("Filósofo %d dejó el palillo %d y %d \n", 
		phnum + 1, LEFT + 1, phnum + 1); 
	printf("Filósofo %d está pensando\n", phnum + 1); 

	test(LEFT); 
	test(RIGHT); 

	sem_post(&mutex); 
} 

void* philospher(void* num) 
{ 

	while (1) { 

		int* i = num; 

		sleep(1); 

		take_fork(*i); 

		sleep(0); 

		put_fork(*i); 
	} 
} 

int main() 
{ 

	int i; 
	pthread_t thread_id[N]; 

	// Inicializacion de los semáforos 
	sem_init(&mutex, 0, 1); 

	for (i = 0; i < N; i++) 

		sem_init(&S[i], 0, 0); 

	for (i = 0; i < N; i++) { 

		// Creacion de los procesos 
		pthread_create(&thread_id[i], NULL, 
					philospher, &phil[i]); 

		printf("Filósofo %d está pensando\n", i + 1); 
	} 

	for (i = 0; i < N; i++) 

		pthread_join(thread_id[i], NULL); 
} 
