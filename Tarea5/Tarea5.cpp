#include<stdio.h>
#include<conio.h>
#include<pthread.h>
#include<semaphore.h>
#include<time.h>
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

#define D 100        //Para los delays, cuando se necesite visualizar.

int N;              //Número de elementos a ordenar.
int lista[100];     //Lista de elementos a ordenar.

sem_t mutex;        //Semáforo que actúa como mutex.

void *menu(void *ID);
void bubbleSort(int id);
void cocktailSort(int id);
void insertionSort(int id);
void bucketSort(int id);
void countingSort(int id);
void mergeSort(int id);
void binarythreeSort(int id);
//void ordenamiento(int izq, int der, int listaOrd[], int id, int dir);
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
    int v = 2;
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
        case 0: bubbleSort(0);
                break;
        case 1: cocktailSort(1);
                break;
        case 2: insertionSort(2);
                break;
        case 3: bucketSort(3);
                break;
        case 4: countingSort(4);
                break;
        case 5: mergeSort(5);
                break;
        case 6: binarythreeSort(6);
                break;
       default: settextstyle(0, 0, 2);
                outtextxy(500, 500, (char *)"Este algoritmo no existe.");
                break;
    }
}

void bubbleSort(int id)
{
    int i,  j, k;          //Contadores.
    int temp;           //Para almacenamiento temporal.
    int listaOrd[N];    //Para ordenar la lista.
    //Para medir el tiempo de ejecución.
    clock_t cronometro;
    double tiempo;
    char T[8];

    for(i = 0; i < N; i++)
    {
        listaOrd[i] = lista[i];
        //objeto(325+i*50, 200, listaOrd[i]);
    }

    cronometro = clock();   //Inicia el cronómetro.

    for(i = 1; i < N; i++)
    {
        for(j = 0; j < N - i; j++)
        {
            if(listaOrd[j] > listaOrd[j+1])
            {
                //Para la parte gráfica.
                //ordenamiento(j, j+1, listaOrd, id, 0);
                for(k = 0; k < ((j+1) - j)*50; k++)
                {
                    setcolor(GREEN);
                    objeto(325+j*50+k, 200+id*50, listaOrd[j]);
                    objeto(325+(j+1)*50-k, 200+id*50, listaOrd[(j+1)]);
                    delay(D);
                    setcolor(BLACK);
                    objeto(325+j*50+k, 200+id*50, listaOrd[j]);
                    objeto(325+(j+1)*50-k, 200+id*50, listaOrd[(j+1)]);
                }

                setcolor(WHITE);
                objeto(325+j*50+k, 200+id*50, listaOrd[j]);
                objeto(325+(j+1)*50-k, 200+id*50, listaOrd[(j+1)]);

                //Para la parte de arreglos.
                temp = listaOrd[j];
                listaOrd[j] = listaOrd[j+1];
                listaOrd[j+1] = temp;
            }
        }
    }

    //Detiene el cronómetro e imprime el tiempo.
    cronometro = clock() - cronometro;
    tiempo = ((double)cronometro)/CLOCKS_PER_SEC;
    sprintf(T, "%0.2f s", tiempo);
    settextstyle(0, 0, 2);
    outtextxy(325+N*50, 200+id*50, T);
}

void cocktailSort(int id)
{
    int i,  j, k;          //Contadores.
    int temp;           //Para almacenamiento temporal.
    int sw;             //Para
    int listaOrd[N];    //Para ordenar la lista.
    //Para medir el tiempo de ejecución.
    clock_t cronometro;
    double tiempo;
    char T[8];

    for(i = 0; i < N; i++)
    {
        listaOrd[i] = lista[i];
    }

    cronometro = clock();   //Inicia el cronómetro.

    sw = 1;
    for(i = 0; i < N - 1 && sw == 1; i++)
    {
        sw = 0;
        for(j = 0; j < N - 1 - i; j++)
        {
            //Bubble Sort de izquierda a derecha.
            if(listaOrd[j] > listaOrd[j+1])
            {
                //ordenamiento(j, j+1, listaOrd, id, 0);
                for(k = 0; k < ((j+1) - j)*50; k++)
                {
                    setcolor(GREEN);
                    objeto(325+j*50+k, 200+id*50, listaOrd[j]);
                    objeto(325+(j+1)*50-k, 200+id*50, listaOrd[(j+1)]);
                    delay(D);
                    setcolor(BLACK);
                    objeto(325+j*50+k, 200+id*50, listaOrd[j]);
                    objeto(325+(j+1)*50-k, 200+id*50, listaOrd[(j+1)]);
                }

                setcolor(WHITE);
                objeto(325+j*50+k, 200+id*50, listaOrd[j]);
                objeto(325+(j+1)*50-k, 200+id*50, listaOrd[(j+1)]);

                temp = listaOrd[j+1];
                listaOrd[j+1] = listaOrd[j];
                listaOrd[j] = temp;
                //sw = 1;
            }
        }

        for(j = 0; j < N - 1 - i; j++)
        {
            //Bubble Sort de derecha a izquierda.
            if(listaOrd[N-1-j] < listaOrd[N-2-j])
            {
                //ordenamiento(N-2-j, N-1-j, listaOrd, id, 1);
                for(k = 0; k < ((N-1-j) - (N-2-j))*50; k++)
                {
                    setcolor(RED);
                    objeto(325+(N-2-j)*50+k, 200+id*50, listaOrd[(N-2-j)]);
                    objeto(325+(N-1-j)*50-k, 200+id*50, listaOrd[(N-1-j)]);
                    delay(D);
                    setcolor(BLACK);
                    objeto(325+(N-2-j)*50+k, 200+id*50, listaOrd[(N-2-j)]);
                    objeto(325+(N-1-j)*50-k, 200+id*50, listaOrd[(N-1-j)]);
                }

                setcolor(WHITE);
                objeto(325+(N-2-j)*50+k, 200+id*50, listaOrd[(N-2-j)]);
                objeto(325+(N-1-j)*50-k, 200+id*50, listaOrd[(N-1-j)]);

                temp = listaOrd[N-2-j];
                listaOrd[N-2-j] = listaOrd[N-1-j];
                listaOrd[N-1-j] = temp;
                sw = 1;
            }
        }
    }

    //Detiene el cronómetro e imprime el tiempo.
    cronometro = clock() - cronometro;
    tiempo = ((double)cronometro)/CLOCKS_PER_SEC;
    sprintf(T, "%0.2f s", tiempo);
    settextstyle(0, 0, 2);
    outtextxy(325+N*50, 200+id*50, T);
}

void insertionSort(int id)
{
    int i,  j, k;          //Contadores.
    int temp;           //Para almacenamiento temporal.
    int listaOrd[N];    //Para ordenar la lista.
    //Para medir el tiempo de ejecución.
    clock_t cronometro;
    double tiempo;
    char T[8];

    for(i = 0; i < N; i++)
    {
        listaOrd[i] = lista[i];
    }

    cronometro = clock();   //Inicia el cronómetro.

    for (i = 1 ; i <= N - 1; i++)
    {
        j = i;

        while (j > 0 && listaOrd[j] < listaOrd[j-1])
        {
            //ordenamiento(j-1, j, listaOrd, id, 0);
            for(k = 0; k < (j - (j-1))*50; k++)
            {
                setcolor(GREEN);
                objeto(325+(j-1)*50+k, 200+id*50, listaOrd[(j-1)]);
                setcolor(RED);
                objeto(325+j*50-k, 200+id*50, listaOrd[j]);
                delay(D);
                setcolor(BLACK);
                objeto(325+(j-1)*50+k, 200+id*50, listaOrd[(j-1)]);
                objeto(325+j*50-k, 200+id*50, listaOrd[j]);
            }

            if (j==i)
            {
                setcolor(BLUE);
            }
            else
            {
                setcolor(WHITE);
            }
            objeto(325+(j-1)*50+k, 200+id*50, listaOrd[(j-1)]);
            setcolor(WHITE);
            objeto(325+j*50-k, 200+id*50, listaOrd[j]);

            temp = listaOrd[j];
            listaOrd[j] = listaOrd[j-1];
            listaOrd[j-1] = temp;
            j--;
        }
    }

    //Detiene el cronómetro e imprime el tiempo.
    cronometro = clock() - cronometro;
    tiempo = ((double)cronometro)/CLOCKS_PER_SEC;
    sprintf(T, "%0.2f s", tiempo);
    settextstyle(0, 0, 2);
    outtextxy(325+N*50, 200+id*50, T);
}

void bucketSort(int id)
{
    int i,  j;          //Contadores.
    int temp;           //Para almacenamiento temporal.
    int listaOrd[N];    //Para ordenar la lista.
    //Para medir el tiempo de ejecución.
    clock_t cronometro;
    double tiempo;
    char T[8];

    for(i = 0; i < N; i++)
    {
        listaOrd[i] = lista[i];
    }

    cronometro = clock();   //Inicia el cronómetro.

    //ALGORITMO

    //Detiene el cronómetro e imprime el tiempo.
    cronometro = clock() - cronometro;
    tiempo = ((double)cronometro)/CLOCKS_PER_SEC;
    sprintf(T, "%0.2f s", tiempo);
    settextstyle(0, 0, 2);
    outtextxy(325+N*50, 200+id*50, T);
}

void countingSort(int id)
{
    int i,  j;          //Contadores.
    int temp;           //Para almacenamiento temporal.
    int listaOrd[N];    //Para ordenar la lista.
    //Para medir el tiempo de ejecución.
    clock_t cronometro;
    double tiempo;
    char T[8];

    for(i = 0; i < N; i++)
    {
        listaOrd[i] = lista[i];
    }

    cronometro = clock();   //Inicia el cronómetro.

    //ALGORITMO

    //Detiene el cronómetro e imprime el tiempo.
    cronometro = clock() - cronometro;
    tiempo = ((double)cronometro)/CLOCKS_PER_SEC;
    sprintf(T, "%0.2f s", tiempo);
    settextstyle(0, 0, 2);
    outtextxy(325+N*50, 200+id*50, T);
}

void mergeSort(int id)
{
    int i,  j;          //Contadores.
    int temp;           //Para almacenamiento temporal.
    int listaOrd[N];    //Para ordenar la lista.
    //Para medir el tiempo de ejecución.
    clock_t cronometro;
    double tiempo;
    char T[8];

    for(i = 0; i < N; i++)
    {
        listaOrd[i] = lista[i];
    }

    cronometro = clock();   //Inicia el cronómetro.

    //ALGORITMO

    //Detiene el cronómetro e imprime el tiempo.
    cronometro = clock() - cronometro;
    tiempo = ((double)cronometro)/CLOCKS_PER_SEC;
    sprintf(T, "%0.2f s", tiempo);
    settextstyle(0, 0, 2);
    outtextxy(325+N*50, 200+id*50, T);
}

void binarythreeSort(int id)
{
    int i,  j;          //Contadores.
    int temp;           //Para almacenamiento temporal.
    int listaOrd[N];    //Para ordenar la lista.
    //Para medir el tiempo de ejecución.
    clock_t cronometro;
    double tiempo;
    char T[8];

    for(i = 0; i < N; i++)
    {
        listaOrd[i] = lista[i];
    }

    cronometro = clock();   //Inicia el cronómetro.

    //ALGORITMO

    //Detiene el cronómetro e imprime el tiempo.
    cronometro = clock() - cronometro;
    tiempo = ((double)cronometro)/CLOCKS_PER_SEC;
    sprintf(T, "%0.2f s", tiempo);
    settextstyle(0, 0, 2);
    outtextxy(325+N*50, 200+id*50, T);
}

//Ordena dos elementos de la lista en la parte gráfica.
//Intentar adaptarlo para varios algoritmos complica mucho la vida.
/*
void ordenamiento(int izq, int der, int listaOrd[], int id, int dir)
{
    int k;

    for(k = 0; k < (der - izq)*50; k++)
    {
        setcolor(GREEN);
        objeto(325+izq*50+k, 200+id*50, listaOrd[izq]);
        objeto(325+der*50-k, 200+id*50, listaOrd[der]);
        delay(D);
        setcolor(BLACK);
        objeto(325+izq*50+k, 200+id*50, listaOrd[izq]);
        objeto(325+der*50-k, 200+id*50, listaOrd[der]);
    }

    setcolor(WHITE);
    objeto(325+izq*50+k, 200+id*50, listaOrd[izq]);
    objeto(325+der*50-k, 200+id*50, listaOrd[der]);
}
*/

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
