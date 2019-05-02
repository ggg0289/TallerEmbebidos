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
https://www.geeksforgeeks.org/insertion-sort/
http://www.ccodechamp.com/c-program-for-selection-sort-algorithm-c-code-champs/
http://www.ccodechamp.com/c-program-of-gnome-sort-algorithm-c-code-champ/
https://www.geeksforgeeks.org/gnome-sort-a-stupid-one/

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
void selectionSort(int id);
void gnomeSort(int id);
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
      "Selection Sort",
      "Gnome Sort",
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
        case 3: selectionSort(3);
                break;
        case 4: gnomeSort(4);
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

//Compara n con n+1 y los ordena, n++, repetir hasta ordenar todo.
void bubbleSort(int id)
{
    int i,  j, k;       //Contadores.
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

    //Recorre el arreglo.
    for(i = 1; i < N; i++)
    {
        //Compara dos elementos.
        for(j = 0; j < N - i; j++)
        {
            //Si están desordeados, los intercambia.
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

//Hace un Bubble de izquierda a derecha y otro de derecha a izquierda, repetir hasta ordenar todo.
void cocktailSort(int id)
{
    int i,  j, k;       //Contadores.
    int temp;           //Para almacenamiento temporal.
    int sw;             //Para para indicar el fin de una ronda.
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
    //Para recorrer el arreglo.
    for(i = 0; i < N - 1 && sw == 1; i++)
    {
        sw = 0;
        //Para comparar elementos.
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

        //Para comparar elementos.
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

//Compara n con los elementos < n y lo coloca en donde corresponde de una vez, n++, repetir hasta ordenar todo.
void insertionSort(int id)
{
    int i,  j, k;       //Contadores.
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

    //Para recorrer el arreglo.
    for (i = 1 ; i <= N - 1; i++)
    {
        j = i;
        //Compara y ordena dos elementos, luego hace lo mismo con los elementos anteriores.
        while (j > 0 && listaOrd[j] < listaOrd[j-1])
        {
            //Para la parte gráfica.
            //ordenamiento(j-1, j, listaOrd, id, 0);
            for(k = 0; k < (j - (j-1))*50; k++)
            {
                //El primer elemento del primer ciclo siempre será azul.
                if (j==i)
                {
                    setcolor(BLUE);
                }
                else
                {
                    setcolor(BLACK);
                }
                objeto(325+j*50, 200+id*50, listaOrd[j]);
                //Intercambio.
                setcolor(GREEN);                                        //Elemento anterior.
                objeto(325+(j-1)*50+k, 200+id*50, listaOrd[(j-1)]);
                setcolor(RED);                                          //Elemento presente.
                objeto(325+j*50-k, 200+id*50, listaOrd[j]);
                delay(D);
                setcolor(BLACK);                                        //"Borra" lo que queda al intercambair.
                objeto(325+(j-1)*50+k, 200+id*50, listaOrd[(j-1)]);
                objeto(325+j*50-k, 200+id*50, listaOrd[j]);
            }

            //El primer elemento del primer ciclo siempre será azul.
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

            //Para la parte de arreglos.
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

//Compara n con los elementos > n para determinar el menor e intercambiar, repetir hasta ordenar todo.
void selectionSort(int id)
{
    int i,  j, k, l;    //Contadores.
    int amin, imin;     //Para valores mínimos.
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

    //Para recorrer el arreglo.
    for(i = 0; i <= N-1; i++)
    {
        //Presuntos valores mínimos.
        imin = i;
        amin = listaOrd[i];

        //Para compararlos con los valores posteriores.
        for(j = i+1; j <= N-1; j++)
        {
            //Para asegurar de que siempre se guarde el menor.
            if(listaOrd[j] < amin)
            {
                imin = j;
                amin = listaOrd[j];
            }
        }

        //Hace el intercambio.
        if(imin != 1)
        {
            //Para la parte gráfica.
            for(k = 0; k < (imin - i)*50; k++)
            {
                //Estos dos fors eson par que no se borren los objetos, hay que reimprimirlos.
                for(l = i+1; l < imin; l++)
                {
                    setcolor(WHITE);
                    objeto(325+l*50, 200+id*50, listaOrd[l]);
                }

                for(l = imin+1; l < N; l++)
                {
                    setcolor(WHITE);
                    objeto(325+l*50, 200+id*50, listaOrd[l]);
                }

                setcolor(BLUE);                                     //Presunto mínimo.
                objeto(325+i*50, 200+id*50, listaOrd[i]);
                setcolor(RED);                                      //Verdadero mínimo.
                objeto(325+imin*50, 200+id*50, listaOrd[imin]);
                //Intercambio.
                setcolor(GREEN);
                objeto(325+i*50+k, 200+id*50, listaOrd[i]);
                objeto(325+imin*50-k, 200+id*50, listaOrd[imin]);
                delay(D);
                setcolor(BLACK);
                objeto(325+i*50+k, 200+id*50, listaOrd[i]);
                objeto(325+imin*50-k, 200+id*50, listaOrd[imin]);
            }

            setcolor(WHITE);
            objeto(325+i*50+k, 200+id*50, listaOrd[i]);
            objeto(325+imin*50-k, 200+id*50, listaOrd[imin]);

            //Para la parte de arreglos.
            temp = listaOrd[i];
            listaOrd[i] = listaOrd[imin];
            listaOrd[imin] = temp;
        }
    }

    //Detiene el cronómetro e imprime el tiempo.
    cronometro = clock() - cronometro;
    tiempo = ((double)cronometro)/CLOCKS_PER_SEC;
    sprintf(T, "%0.2f s", tiempo);
    settextstyle(0, 0, 2);
    outtextxy(325+N*50, 200+id*50, T);
}

//Compara n con los elementos < n y lo coloca en donde corresponde mediante intercambios, n++, repetir hasta ordenar todo.
void gnomeSort(int id)
{
    int i, k;          //Contadores.
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

    i = 0;
    while(i < N)
    {
        if (i == 0 || listaOrd[i] >= listaOrd[i - 1])
        {
            i++;
        }
        else
        {
            //Para la pate gráfica.
            for(k = 0; k < (i - (i-1))*50; k++)
            {
                setcolor(GREEN);
                objeto(325+(i-1)*50+k, 200+id*50, listaOrd[(i-1)]);
                objeto(325+i*50-k, 200+id*50, listaOrd[i]);
                delay(D);
                setcolor(BLACK);
                objeto(325+(i-1)*50+k, 200+id*50, listaOrd[(i-1)]);
                objeto(325+i*50-k, 200+id*50, listaOrd[i]);
            }

            setcolor(WHITE);
            objeto(325+(i-1)*50+k, 200+id*50, listaOrd[(i-1)]);
            objeto(325+i*50-k, 200+id*50, listaOrd[i]);

            //Para la parte de arreglos.
            temp = listaOrd[i];
            listaOrd[i] = listaOrd[i - 1];
            listaOrd[i - 1] = temp;
            i--;
        }
    }

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
//Intentar adaptarlo para varios algoritmos complica mucho la vida, ahora cada uno imprime lo suyo.
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
