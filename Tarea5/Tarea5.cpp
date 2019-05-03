#include<stdio.h>
#include<pthread.h>
#include<time.h>
#include<graphics.h>

/*
Algoritmos De Ordenamiento.
Algoritnmos basados en:
http://www.ccodechamp.com/c-program-of-bubble-sort-algorithm-c-code-champs/
http://www.ccodechamp.com/c-program-for-cocktail-sort-algorithm-c-code-champ/
http://www.ccodechamp.com/c-program-for-insertion-sort-algorithm/
https://www.geeksforgeeks.org/insertion-sort/
https://www.geeksforgeeks.org/odd-even-sort-brick-sort/
https://www.geeksforgeeks.org/gnome-sort-a-stupid-one/
http://www.ccodechamp.com/c-program-for-selection-sort-algorithm-c-code-champs/
http://www.ccodechamp.com/c-program-for-comb-sort-algorithm-c-code-champ/
http://www.ccodechamp.com/c-program-for-quick-sort-algorithm/
Animación basada en:
https://c.happycodings.com/beginners-lab-assignments/code91.html
*/

#define D 10            //Para los delays, cuando se necesite visualizar.
#define MNX 25          //Margen en x para los nombres.
#define MNY 25         //Margen en y para los nombres.
#define MLX MNX+240     //Margen en x para los elementos iniciales.
#define MLY MNY+10      //Margen en y para los elementos iniciales.
#define MOX MLX         //Margen en x para los elementos a ordenar.
#define MOY MLY+50      //Margen en y para los elementos a ordenar.
#define MBY MOY+50      //Margen en y para los elementos a ordenar uando bajan.
#define ESP 50          //Espaciado enre elementos.

int N;              //Número de elementos a ordenar.
int lista[100];     //Lista de elementos a ordenar.

pthread_mutex_t mutex;

void *menu(void *ID);
void bubbleSort(int id);
void cocktailSort(int id);
void insertionSort(int id);
void oddevenSort(int id);
void selectionSort(int id);
void combSort(int id);
void shellSort(int id);
int newGap(int gap);
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
      "Odd-Even Sort",
      "Selection Sort",
      "Comb Sort",
      "Quick Sort"
    };                  //Nombres de los algoritmos.

    printf("\n\tALGORITMOS DE ORDENAMIENTO - INGRESO DE DATOS\n");

    printf("\nIngrese el numero de elementos a ordenar: " );
    scanf("%d", &N);
    printf("\n" );

    for(i = 0; i < N; i++)
    {
        printf("Ingrese el elemento %d: ", i+1);
        scanf("%d", &lista[i]);
    }

    initwindow(1000, 700, "ALGORITMOS DE ORDENAMIENTO - EJECUCIÓN");  //Iniciar graphics.

    //Arreglos para variables de los hilos.
    pthread_t hiloID[7];        //Identificador.
    int hiloRetorno[7];         //Valor de retorno.

    pthread_mutex_init(&mutex, NULL);     //Inicializar el mutex.

    //Imprimir los nombres y los elementos.
    int INT = 50;    //Interlineado.
    for(i = 0; i < 8; i++)
    {
        if (i < 5)
        {
            INT = 50;
        }
        else
        {
            INT = 100;
        }

        settextstyle(4, 0, 1);
        outtextxy(MNX, MNY+i*INT, (char *)sorts[i]);

        for(j = 0; j < N; j++)
        {
            objeto(MLX+j*ESP, MLY+i*INT, lista[j]);
        }
    }
/*
    //Usado para probar que los algoritmos sirven, uno por uno.
    int v = 4;
    hiloRetorno[v] = pthread_create(&hiloID[v], NULL, menu, &v);
    pthread_join(hiloID[v], NULL);
*//*
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
    pthread_mutex_destroy(&mutex);

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
        case 3: oddevenSort(3);
                break;
        case 4: selectionSort(4);
                break;
        case 5: combSort(5);
                break;
        case 6: shellSort(6);
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
                for(k = 0; k < ((j+1) - j)*ESP; k++)
                {
                    setcolor(GREEN);
                    objeto(MOX+j*ESP+k, MOY+id*ESP, listaOrd[j]);
                    objeto(MOX+(j+1)*ESP-k, MOY+id*ESP, listaOrd[(j+1)]);
                    delay(D);
                    setcolor(BLACK);
                    objeto(MOX+j*ESP+k, MOY+id*ESP, listaOrd[j]);
                    objeto(MOX+(j+1)*ESP-k, MOY+id*ESP, listaOrd[(j+1)]);
                }

                setcolor(WHITE);
                objeto(MOX+j*ESP+k, MOY+id*ESP, listaOrd[j]);
                objeto(MOX+(j+1)*ESP-k, MOY+id*ESP, listaOrd[(j+1)]);

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
    outtextxy(MOX+N*ESP, MOY+id*ESP, T);
}

//Hace un Bubble Sort de izquierda a derecha y otro de derecha a izquierda, repetir hasta ordenar todo.
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
        //Bubble Sort de izquierda a derecha.
        for(j = 0; j < N - 1 - i; j++)
        {
            if(listaOrd[j] > listaOrd[j+1])
            {
                for(k = 0; k < ((j+1) - j)*ESP; k++)
                {
                    setcolor(GREEN);
                    objeto(MOX+j*ESP+k, MOY+id*ESP, listaOrd[j]);
                    objeto(MOX+(j+1)*ESP-k, MOY+id*ESP, listaOrd[(j+1)]);
                    delay(D);
                    setcolor(BLACK);
                    objeto(MOX+j*ESP+k, MOY+id*ESP, listaOrd[j]);
                    objeto(MOX+(j+1)*ESP-k, MOY+id*ESP, listaOrd[(j+1)]);
                }

                setcolor(WHITE);
                objeto(MOX+j*ESP+k, MOY+id*ESP, listaOrd[j]);
                objeto(MOX+(j+1)*ESP-k, MOY+id*ESP, listaOrd[(j+1)]);

                temp = listaOrd[j+1];
                listaOrd[j+1] = listaOrd[j];
                listaOrd[j] = temp;
                //sw = 1;
            }
        }

        //Bubble Sort de derecha a izquierda.
        for(j = 0; j < N - 1 - i; j++)
        {
            if(listaOrd[N-1-j] < listaOrd[N-2-j])
            {
                //ordenamiento(N-2-j, N-1-j, listaOrd, id, 1);
                for(k = 0; k < ((N-1-j) - (N-2-j))*ESP; k++)
                {
                    setcolor(RED);
                    objeto(MOX+(N-2-j)*ESP+k, MOY+id*ESP, listaOrd[(N-2-j)]);
                    objeto(MOX+(N-1-j)*ESP-k, MOY+id*ESP, listaOrd[(N-1-j)]);
                    delay(D);
                    setcolor(BLACK);
                    objeto(MOX+(N-2-j)*ESP+k, MOY+id*ESP, listaOrd[(N-2-j)]);
                    objeto(MOX+(N-1-j)*ESP-k, MOY+id*ESP, listaOrd[(N-1-j)]);
                }

                setcolor(WHITE);
                objeto(MOX+(N-2-j)*ESP+k, MOY+id*ESP, listaOrd[(N-2-j)]);
                objeto(MOX+(N-1-j)*ESP-k, MOY+id*ESP, listaOrd[(N-1-j)]);

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
    outtextxy(MOX+N*ESP, MOY+id*ESP, T);
}

//Compara n con los elementos < n y lo coloca en donde corresponde, n++, repetir hasta ordenar todo.
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
            for(k = 0; k < (j - (j-1))*ESP; k++)
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
                objeto(MOX+j*ESP, MOY+id*ESP, listaOrd[j]);
                //Intercambio.
                setcolor(GREEN);                                        //Elemento anterior.
                objeto(MOX+(j-1)*ESP+k, MOY+id*ESP, listaOrd[(j-1)]);
                setcolor(RED);                                          //Elemento presente.
                objeto(MOX+j*ESP-k, MOY+id*ESP, listaOrd[j]);
                delay(D);
                setcolor(BLACK);                                        //"Borra" lo que queda al intercambair.
                objeto(MOX+(j-1)*ESP+k, MOY+id*ESP, listaOrd[(j-1)]);
                objeto(MOX+j*ESP-k, MOY+id*ESP, listaOrd[j]);
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
            objeto(MOX+(j-1)*ESP+k, MOY+id*ESP, listaOrd[(j-1)]);
            setcolor(WHITE);
            objeto(MOX+j*ESP-k, MOY+id*ESP, listaOrd[j]);

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
    outtextxy(MOX+N*ESP, MOY+id*ESP, T);
}

//Aplica Bubble Sort a un número par e impar de parejas, repetir hasta ordenar todo.
void oddevenSort(int id)
{
    int i, k;               //Contadores.
    int temp;               //Para almacenamiento temporal.
    int listaOrd[N];        //Para ordenar la lista.
    bool isSorted = false;  //Control del bucle.

    //Para medir el tiempo de ejecución.
    clock_t cronometro;
    double tiempo;
    char T[8];

    for(i = 0; i < N; i++)
    {
        listaOrd[i] = lista[i];
    }

    cronometro = clock();   //Inicia el cronómetro.

    while (!isSorted)
    {
        isSorted = true;

        //Bubble Sort para el número impar de parejas.
        for (i=1; i<=N-2; i=i+2)
        {
            if (listaOrd[i] > listaOrd[i+1])
            {
                for(k = 0; k < ((i+1) - i)*ESP; k++)
                {
                    setcolor(RED);
                    objeto(MOX+i*ESP+k, MOY+id*ESP, listaOrd[i]);
                    objeto(MOX+(i+1)*ESP-k, MOY+id*ESP, listaOrd[(i+1)]);
                    delay(D);
                    setcolor(BLACK);
                    objeto(MOX+i*ESP+k, MOY+id*ESP, listaOrd[i]);
                    objeto(MOX+(i+1)*ESP-k, MOY+id*ESP, listaOrd[(i+1)]);
                }

                setcolor(WHITE);
                objeto(MOX+i*ESP+k, MOY+id*ESP, listaOrd[i]);
                objeto(MOX+(i+1)*ESP-k, MOY+id*ESP, listaOrd[(i+1)]);

                temp = listaOrd[i+1];
                listaOrd[i+1] = listaOrd[i];
                listaOrd[i] = temp;
                isSorted = false;
              }
        }

        //Bubble Sort para número par de parejas.
        for (int i=0; i<=N-2; i=i+2)
        {
            if (listaOrd[i] > listaOrd[i+1])
            {
                for(k = 0; k < ((i+1) - i)*ESP; k++)
                {
                    setcolor(GREEN);
                    objeto(MOX+i*ESP+k, MOY+id*ESP, listaOrd[i]);
                    objeto(MOX+(i+1)*ESP-k, MOY+id*ESP, listaOrd[(i+1)]);
                    delay(D);
                    setcolor(BLACK);
                    objeto(MOX+i*ESP+k, MOY+id*ESP, listaOrd[i]);
                    objeto(MOX+(i+1)*ESP-k, MOY+id*ESP, listaOrd[(i+1)]);
                }

                setcolor(WHITE);
                objeto(MOX+i*ESP+k, MOY+id*ESP, listaOrd[i]);
                objeto(MOX+(i+1)*ESP-k, MOY+id*ESP, listaOrd[(i+1)]);

                temp = listaOrd[i+1];
                listaOrd[i+1] = listaOrd[i];
                listaOrd[i] = temp;
                isSorted = false;
            }
        }
    }

    //Detiene el cronómetro e imprime el tiempo.
    cronometro = clock() - cronometro;
    tiempo = ((double)cronometro)/CLOCKS_PER_SEC;
    sprintf(T, "%0.2f s", tiempo);
    settextstyle(0, 0, 2);
    outtextxy(MOX+N*ESP, MOY+id*ESP, T);
}

//Compara n con los elementos > n para determinar el menor e intercambiar, repetir hasta ordenar todo.
void selectionSort(int id)
{
    int i,  j, k;       //Contadores.
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
            //Bajar.
            for(k = 0; k < ESP; k++)
            {
                setcolor(BLUE);
                objeto(MOX+i*ESP, MOY+id*ESP, listaOrd[i]);
                setcolor(RED);
                objeto(MOX+imin*ESP, MOY+id*ESP, listaOrd[imin]);

                setcolor(GREEN);
                objeto(MOX+i*ESP, MOY+id*ESP+k, listaOrd[i]);
                delay(D);
                setcolor(BLACK);
                objeto(MOX+i*ESP, MOY+id*ESP+k, listaOrd[i]);

                setcolor(GREEN);
                objeto(MOX+imin*ESP, MOY+id*ESP+k, listaOrd[imin]);
                delay(D);
                setcolor(BLACK);
                objeto(MOX+imin*ESP, MOY+id*ESP+k, listaOrd[imin]);
            }

            setcolor(WHITE);
            objeto(MOX+i*ESP, MOY+id*ESP+k, listaOrd[i]);
            objeto(MOX+imin*ESP, MOY+id*ESP+k, listaOrd[imin]);

            //Intercambiar.
            for(k = 0; k < (imin - i)*ESP; k++)
            {
                setcolor(GREEN);
                objeto(MOX+i*ESP+k, MBY+id*ESP, listaOrd[i]);
                objeto(MOX+imin*ESP-k, MBY+id*ESP, listaOrd[imin]);
                delay(D);
                setcolor(BLACK);
                objeto(MOX+i*ESP+k, MBY+id*ESP, listaOrd[i]);
                objeto(MOX+imin*ESP-k, MBY+id*ESP, listaOrd[imin]);
            }

            setcolor(WHITE);
            objeto(MOX+i*ESP+k, MBY+id*ESP, listaOrd[i]);
            objeto(MOX+imin*ESP-k, MBY+id*ESP, listaOrd[imin]);

            //Subir.
            for(k = ESP; k > 0; k--)
            {
                setcolor(GREEN);
                objeto(MOX+i*ESP, MOY+id*ESP+k, listaOrd[imin]);
                delay(D);
                setcolor(BLACK);
                objeto(MOX+i*ESP, MOY+id*ESP+k, listaOrd[imin]);

                setcolor(GREEN);
                objeto(MOX+imin*ESP, MOY+id*ESP+k, listaOrd[i]);
                delay(D);
                setcolor(BLACK);
                objeto(MOX+imin*ESP, MOY+id*ESP+k, listaOrd[i]);
            }

            setcolor(WHITE);
            objeto(MOX+i*ESP, MOY+id*ESP+k, listaOrd[imin]);
            objeto(MOX+imin*ESP, MOY+id*ESP+k, listaOrd[i]);

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
    outtextxy(MOX+N*ESP, MOY+id*ESP, T);
}

//Compara y ordena n y m distanciados por un gap, gap se reduce, repetir hasta ordenar todo.
void combSort(int id)
{
    int i,  j, k;       //Contadores.
    int temp;           //Para almacenamiento temporal.
    int listaOrd[N];    //Para ordenar la lista.
    int gap = N;        //Gap inicial.
    bool swapped;       //Control para el bucle.

    //Para medir el tiempo de ejecución.
    clock_t cronometro;
    double tiempo;
    char T[8];

    for(i = 0; i < N; i++)
    {
        listaOrd[i] = lista[i];
    }

    cronometro = clock();   //Inicia el cronómetro.

    for (;;)
    {
        gap = newGap(gap);  //Nuevo gap.
        swapped = false;
        //Compara elementos separados por el gap.
        for (i = 0; i < N - gap; i++)
        {
            j = i + gap;
            //Ordena los elementos.
            if (listaOrd[i] > listaOrd[j])
            {
                //Para la parte gráfica.
                //Bajar.
                for(k = 0; k < ESP; k++)
                {
                    setcolor(BLUE);                             //Primer elemento.
                    objeto(MOX+i*ESP, MOY+id*ESP, listaOrd[i]);
                    setcolor(RED);                              //Elemento separado por el gap.
                    objeto(MOX+j*ESP, MOY+id*ESP, listaOrd[j]);

                    setcolor(GREEN);
                    objeto(MOX+i*ESP, MOY+id*ESP+k, listaOrd[i]);
                    delay(D);
                    setcolor(BLACK);
                    objeto(MOX+i*ESP, MOY+id*ESP+k, listaOrd[i]);

                    setcolor(GREEN);
                    objeto(MOX+j*ESP, MOY+id*ESP+k, listaOrd[j]);
                    delay(D);
                    setcolor(BLACK);
                    objeto(MOX+j*ESP, MOY+id*ESP+k, listaOrd[j]);
                }

                setcolor(WHITE);
                objeto(MOX+i*ESP, MOY+id*ESP+k, listaOrd[i]);
                objeto(MOX+j*ESP, MOY+id*ESP+k, listaOrd[j]);

                //Intercambiar.
                for(k = 0; k < (j - i)*ESP; k++)
                {
                    setcolor(GREEN);
                    objeto(MOX+i*ESP+k, MBY+id*ESP, listaOrd[i]);
                    objeto(MOX+j*ESP-k, MBY+id*ESP, listaOrd[j]);
                    delay(D);
                    setcolor(BLACK);
                    objeto(MOX+i*ESP+k, MBY+id*ESP, listaOrd[i]);
                    objeto(MOX+j*ESP-k, MBY+id*ESP, listaOrd[j]);
                }

                setcolor(WHITE);
                objeto(MOX+i*ESP+k, MBY+id*ESP, listaOrd[i]);
                objeto(MOX+j*ESP-k, MBY+id*ESP, listaOrd[j]);

                //Subir.
                for(k = ESP; k > 0; k--)
                {
                    setcolor(GREEN);
                    objeto(MOX+i*ESP, MOY+id*ESP+k, listaOrd[j]);
                    delay(D);
                    setcolor(BLACK);
                    objeto(MOX+i*ESP, MOY+id*ESP+k, listaOrd[j]);

                    setcolor(GREEN);
                    objeto(MOX+j*ESP, MOY+id*ESP+k, listaOrd[i]);
                    delay(D);
                    setcolor(BLACK);
                    objeto(MOX+j*ESP, MOY+id*ESP+k, listaOrd[i]);
                }

                setcolor(WHITE);
                objeto(MOX+i*ESP, MOY+id*ESP+k, listaOrd[j]);
                objeto(MOX+j*ESP, MOY+id*ESP+k, listaOrd[i]);

                //Para la parte de arreglos.
                temp = listaOrd[i];
                listaOrd[i] = listaOrd[i + gap];
                listaOrd[i + gap] = temp;
                swapped = true;
            }
        }
    //Se sale del bucle cundo termina de ordenar.
    if (gap == 1 && !swapped)
        break;
    }

    //Detiene el cronómetro e imprime el tiempo.
    cronometro = clock() - cronometro;
    tiempo = ((double)cronometro)/CLOCKS_PER_SEC;
    sprintf(T, "%0.2f s", tiempo);
    settextstyle(0, 0, 2);
    outtextxy(MOX+N*ESP, MOY+id*ESP, T);
}

//Compara y ordena elementos alejados entre sí, reduce la lejanía, repetir hasta ordenar todo.
void shellSort(int id)
{
    int i, j, k, m;     //Contadores.
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

    //Distanciamiento grande, se va reduciendo.
    for(m = N/2; m > 0 ; m/=2)
    {
        //Ordenar lo que está dentro del rango.
        for(j = m; j < N; j++)
        {
            //Buscar la posición correcta para los elementos.
            for(i = j-m; i >= 0; i-=m)
            {
                //Si están en desorden, ordenarlos.
                if(listaOrd[i+m] >= listaOrd[i])
                    break;
                else
                {
                    for(k = 0; k < ESP; k++)
                    {
                        setcolor(GREEN);
                        objeto(MOX+i*ESP, MOY+id*ESP+k, listaOrd[i]);
                        delay(D);
                        setcolor(BLACK);
                        objeto(MOX+i*ESP, MOY+id*ESP+k, listaOrd[i]);

                        setcolor(GREEN);
                        objeto(MOX+(i+m)*ESP, MOY+id*ESP+k, listaOrd[(i+m)]);
                        delay(D);
                        setcolor(BLACK);
                        objeto(MOX+(i+m)*ESP, MOY+id*ESP+k, listaOrd[(i+m)]);
                    }

                    setcolor(WHITE);
                    objeto(MOX+i*ESP, MOY+id*ESP+k, listaOrd[i]);
                    objeto(MOX+(i+m)*ESP, MOY+id*ESP+k, listaOrd[(i+m)]);

                    //Intercambiar.
                    for(k = 0; k < ((i+m) - i)*ESP; k++)
                    {
                        setcolor(GREEN);
                        objeto(MOX+i*ESP+k, MBY+id*ESP, listaOrd[i]);
                        objeto(MOX+(i+m)*ESP-k, MBY+id*ESP, listaOrd[(i+m)]);
                        delay(D);
                        setcolor(BLACK);
                        objeto(MOX+i*ESP+k, MBY+id*ESP, listaOrd[i]);
                        objeto(MOX+(i+m)*ESP-k, MBY+id*ESP, listaOrd[(i+m)]);
                    }

                    setcolor(WHITE);
                    objeto(MOX+i*ESP+k, MBY+id*ESP, listaOrd[i]);
                    objeto(MOX+(i+m)*ESP-k, MBY+id*ESP, listaOrd[(i+m)]);

                    //Subir.
                    for(k = ESP; k > 0; k--)
                    {
                        setcolor(GREEN);
                        objeto(MOX+i*ESP, MOY+id*ESP+k, listaOrd[(i+m)]);
                        delay(D);
                        setcolor(BLACK);
                        objeto(MOX+i*ESP, MOY+id*ESP+k, listaOrd[(i+m)]);

                        setcolor(GREEN);
                        objeto(MOX+(i+m)*ESP, MOY+id*ESP+k, listaOrd[i]);
                        delay(D);
                        setcolor(BLACK);
                        objeto(MOX+(i+m)*ESP, MOY+id*ESP+k, listaOrd[i]);
                    }

                    setcolor(WHITE);
                    objeto(MOX+i*ESP, MOY+id*ESP+k, listaOrd[(i+m)]);
                    objeto(MOX+(i+m)*ESP, MOY+id*ESP+k, listaOrd[i]);

                    temp = listaOrd[i];
                    listaOrd[i] = listaOrd[i+m];
                    listaOrd[i+m] = temp;
                }
            }
        }
    }

    //Detiene el cronómetro e imprime el tiempo.
    cronometro = clock() - cronometro;
    tiempo = ((double)cronometro)/CLOCKS_PER_SEC;
    sprintf(T, "%0.2f s", tiempo);
    settextstyle(0, 0, 2);
    outtextxy(MOX+N*ESP, MOY+id*ESP, T);
}

//Crea los gaps para Comb Sort.
int newGap(int gap)
{
    gap = (gap * 10) / 13;
    if (gap == 9 || gap == 10)
        gap = 11;
    if (gap < 1)
        gap = 1;
    return gap;
}

//Ordena dos elementos de la lista en la parte gráfica.
//Intentar adaptarlo para varios algoritmos complica mucho la vida, ahora cada uno imprime lo suyo.
/*void ordenamiento(int izq, int der, int listaOrd[], int id, int dir)
{
    int k;

    //Bajar.
    for(k = 0; k < ESP; k++)
    {
        setcolor(GREEN);
        objeto(MOX+izq*ESP, MOY+id*ESP+k, listaOrd[izq]);
        delay(D);
        setcolor(BLACK);
        objeto(MOX+izq*ESP, MOY+id*ESP+k, listaOrd[izq]);

        setcolor(GREEN);
        objeto(MOX+der*ESP, MOY+id*ESP+k, listaOrd[der]);
        delay(D);
        setcolor(BLACK);
        objeto(MOX+der*ESP, MOY+id*ESP+k, listaOrd[der]);
        }

        setcolor(WHITE);
        objeto(MOX+izq*ESP, MOY+id*ESP+k, listaOrd[izq]);
        objeto(MOX+der*ESP, MOY+id*ESP+k, listaOrd[der]);

    //Intercambiar.
    for(k = 0; k < (der - izq)*ESP; k++)
    {
        setcolor(GREEN);
        objeto(MOX+izq*ESP+k, MBY+id*ESP, listaOrd[izq]);
        objeto(MOX+der*ESP-k, MBY+id*ESP, listaOrd[der]);
        delay(D);
        setcolor(BLACK);
        objeto(MOX+izq*ESP+k, MBY+id*ESP, listaOrd[izq]);
        objeto(MOX+der*ESP-k, MBY+id*ESP, listaOrd[der]);
    }

    setcolor(WHITE);
    objeto(MOX+izq*ESP+k, MBY+id*ESP, listaOrd[izq]);
    objeto(MOX+der*ESP-k, MBY+id*ESP, listaOrd[der]);

    //Subir.
    for(k = ESP; k > 0; k--)
    {
        setcolor(GREEN);
        objeto(MOX+izq*ESP, MOY+id*ESP+k, listaOrd[der]);
        delay(D);
        setcolor(BLACK);
        objeto(MOX+izq*ESP, MOY+id*ESP+k, listaOrd[der]);

        setcolor(GREEN);
        objeto(MOX+der*ESP, MOY+id*ESP+k, listaOrd[izq]);
        delay(D);
        setcolor(BLACK);
        objeto(MOX+der*ESP, MOY+id*ESP+k, listaOrd[izq]);
    }

    setcolor(WHITE);
    objeto(MOX+izq*ESP, MOY+id*ESP+k, listaOrd[der]);
    objeto(MOX+der*ESP, MOY+id*ESP+k, listaOrd[izq]);
}*/

//Crea los objetos de la parte gráfica.
void objeto(int x, int y, int num)
{
    //Protegido por mutex porque va a ser usado por todos los algoritmos.
    pthread_mutex_lock(&mutex);   //Mutex lock.

    char dato[8];
    sprintf(dato, "%d", num);
    circle(x, y, 15);
    settextstyle(0, 0, 2);
    outtextxy(x-5, y-9, dato);

    pthread_mutex_unlock(&mutex);   //Mutex unlock.
}
