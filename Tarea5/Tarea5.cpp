#include<stdio.h>
#include<conio.h>
#include<pthread.h>
#include <semaphore.h>
#include<graphics.h>

/*
Algoritmos De Ordenamiento.
Algoritnmos basados en:
http://www.ccodechamp.com/c-program-of-bubble-sort-algorithm-c-code-champs/
http://www.ccodechamp.com/c-program-for-cocktail-sort-algorithm-c-code-champ/
http://www.ccodechamp.com/c-program-for-insertion-sort-algorithm/
http://www.ccodechamp.com/c-program-for-bucket-sort-algorithm/
http://www.ccodechamp.com/c-program-for-counting-sort-algorithm/
http://www.ccodechamp.com/c-program-of-merge-sort-algorithm-c-code-champ/
http://www.ccodechamp.com/c-program-for-binary-tree-sort-algorithm/
Animación basada en:
https://c.happycodings.com/beginners-lab-assignments/code91.html
*/

#define D 20        //Para los delays, cuando se necesite visualizar.

int N;              //Número de elementos a ordenar.
int lista[100];     //Lista de elementos a ordenar.
int tiempos[7];     //Tiempos de ejecución de cada algoritmo.

sem_t mutex;            //Semáforo que actúa como mutex.

void *menu(void *ID);
void bubbleSort();
void cocktailSort();
void insertionSort();
void bucketSort();
void countingSort();
void mergeSort();
void binarythreeSort();
void ordenamiento(int izq, int der, int listaOrd[]);
void objeto(int x, int y, int num);

int main()
{
    int i, j;              //Contadores para los for.
    char sorts[8][25] =
    { "Lista Original",
      "Bubble Sort",
      "Cocktail Sort",
      "Insertion Sort",
      "Bucket Sort",
      "Counting Sort",
      "Merge Sort",
      "Binary Tree Sort"
    };                  //Nombres de los algoritmos.

    printf("\n\tALGORITMOS DE ORDENAMIENTO\n");

    printf("\nIngrese el numero de elementos a ordenar: " );
    scanf("%d", &N);
    printf("\n" );

    for(i = 0; i < N; i++)
    {
        printf("Ingrese el elemento %d: ", i+1);
        scanf("%d", &lista[i]);
    }

    //Arreglos para variables de los hilos.
    pthread_t hiloID[7];    //Identificador.
    int hiloRetorno[7];     //Valor de retorno.

    initwindow(1000, 600);  //Iniciar graphics.
    settextstyle(4, 0, 3);
    outtextxy(250, 50, (char *)"ALGORITMOS DE ORDENAMIENTO");

    //Imprimir los nombres y los arreglos.
    for(i = 0; i < 8; i++)
    {
        settextstyle(4, 0, 1);
        outtextxy(50, 140+i*50, (char *)sorts[i]);

        for(j = 0; j < N; j++)
        {
            objeto(325+j*50, 150+i*50, lista[j]);
        }
    }
/*
    //Usado para hacer experimentos.
    for(i = 0; i < N; i++)
    {
        objeto(325+i*50, 150, lista[i]);
    }
*/
    //Usado para probar que los algoritmos sirven, uno por uno.
    int v = 0;
    hiloRetorno[v] = pthread_create(&hiloID[v], NULL, menu, &v);
    pthread_join(hiloID[v], NULL);

 /*
    //Creación de un hilo por algoritmo.
    for (i = 0; i < 7; i++)
    {
        hiloRetorno[i] = pthread_create(&hiloID[i], NULL, menu, &i);
    }

    //Esperar a que todos los hilos terminen.
    for (i = 0; i < 7; i++){
        pthread_join(hiloID[i], NULL);
    }
*/
    getch();
    closegraph();   //Finalizar graphics.
    printf("\nActividades concluidas. Presione una tecla para salir.\n");
    return 0;
}

//Menú para que cada hilo use el algoritmo que le corresponde.
void *menu(void *ID)
{
    int *id = (int *)ID;
    switch (*id)
    {
        case 0: bubbleSort();
                break;
        case 1: cocktailSort();
                break;
        case 2: insertionSort();
                break;
        case 3: bucketSort();
                break;
        case 4: countingSort();
                break;
        case 5: mergeSort();
                break;
        case 6: binarythreeSort();
                break;
       default: settextstyle(0, 0, 2);
                outtextxy(500, 500, (char *)"Este algoritmo no existe.");
                break;
    }
}

void bubbleSort()
{
    int i,  j;          //Contadores.
    int temp;           //Para almacenamiento temporal.
    int listaOrd[N];    //Para ordenar la lista.

    for(i = 0; i < N; i++)
    {
        listaOrd[i] = lista[i];
        //objeto(325+i*50, 200, listaOrd[i]);
    }

    for(i = 1; i < N; i++)
    {
        for(j = 0; j < N - i; j++)
        {
            if(listaOrd[j] > listaOrd[j+1])
            {
                //Para la parte gráfica.
                ordenamiento(j, j+1, listaOrd);
                //Para la parte de arreglos.
                temp = listaOrd[j];
                listaOrd[j] = listaOrd[j+1];
                listaOrd[j+1] = temp;
            }
        }
    }
}

void cocktailSort()
{
}

void insertionSort()
{
}

void bucketSort()
{
}

void countingSort()
{
}

void mergeSort()
{
}

void binarythreeSort()
{
}

//Para el Bubble Sort, ordena dos elementos de la lista en la parte gráfica.
void ordenamiento(int izq, int der, int listaOrd[])
{
    int i;

    for(i = 0; i < (der - izq)*50; i++)
    {
        setcolor(GREEN);
        objeto(325+izq*50+i, 200, listaOrd[izq]);
        objeto(325+der*50-i, 200, listaOrd[der]);
        delay(D);
        setcolor(0);
        objeto(325+izq*50+i, 200, listaOrd[izq]);
        objeto(325+der*50-i, 200, listaOrd[der]);
    }

    setcolor(WHITE);
    objeto(325+izq*50+i, 200, listaOrd[izq]);
    objeto(325+der*50-i, 200, listaOrd[der]);
}

//Crea los objetos de la parte gráfica.
void objeto(int x, int y, int num)
{
    //Protegido por mutex porque va a ser usado por todos los algoritmos.
    sem_wait(&mutex);   //Mutex lock.

    char dato[8];
    sprintf(dato, "%d", num);
    circle(x, y, 15);
    settextstyle(0, 0, 2);
    outtextxy(x-3, y-10, dato);

    sem_post(&mutex);   //Mutex unlock.
}
