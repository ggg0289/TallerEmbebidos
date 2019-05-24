#include<iostream>
#include<queue>
#include<pthread.h>
#include<time.h>
#include<graphics.h>
using namespace std;

/*
NOTA: Pasando parámetros con arreglos de colas y mutex globales.
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

#define D 0             //Para los delays, cuando se necesite visualizar.
#define MNX 25          //Margen en x para los nombres.
#define MNY 100          //Margen en y para los nombres.
#define MLX MNX+240     //Margen en x para los elementos iniciales.
#define MLY MNY+10      //Margen en y para los elementos iniciales.
#define MOX MLX         //Margen en x para los elementos a ordenar.
#define MOY MLY+50      //Margen en y para los elementos a ordenar.
#define MBY MOY+50      //Margen en y para los elementos a ordenar uando bajan.
#define ESP 50          //Espaciado enre elementos.
#define INT 50         //Interlineado.

int N;              //Número de elementos a ordenar.
int *lista;         //Lista de elementos a ordenar; el puntero se convertirá en un arreglo.

//Para los mensajes.
struct Parametros {
    int inIzq;
    int inDer;
    int valIzq;
    int valDer;
};

queue<Parametros> cola[7];                              //Cola de mensajes.

pthread_mutex_t mutex[7] = {PTHREAD_MUTEX_INITIALIZER};      //Crear e inicializar el mutex.

//Para medir el tiempo de ejecución.
clock_t cronometro[7];
double tiempo[7];
char T[7][8];

//Funciones prototipo.
void *menu(void *ID);
void bubbleSort(int id);
void cocktailSort(int id);
void insertionSort(int id);
void oddevenSort(int id);
void selectionSort(int id);
void combSort(int id);
void shellSort(int id);
int newGap(int gap);
void *ordenamiento(void *ID);
void objeto(int x, int y, int num);

int main()
{
    int i, j;                                   //Contadores para los for.
    int sortID[7] = { 0, 1, 2, 3, 4, 5, 6 };    //Identificaci[on para los algoritmos.
    char sorts[7][25] =
    { "Bubble Sort",
      "Cocktail Sort",
      "Insertion Sort",
      "Odd-Even Sort",
      "Selection Sort",
      "Comb Sort",
      "Quick Sort"
    };                  //Nombres de los algoritmos.

    cout << "\n\tALGORITMOS DE ORDENAMIENTO - INGRESO DE DATOS\n";

    cout << "\nIngrese el numero de elementos a ordenar: ";
    cin >> N;
    cout << "\n";

    lista = (int *)calloc(N, sizeof(int));      //Conversión de puntero a arreglo.

    for(i = 0; i < N; i++)
    {
        cout << "Ingrese el elemento " << i+1 << ": ";
        cin >> lista[i];
    }

    initwindow(getmaxwidth(), 600, "ALGORITMOS DE ORDENAMIENTO - EJECUCIÓN");  //Iniciar graphics.

    //Arreglos para variables de los hilos.
    pthread_t hiloID[14];        //Identificador.
    int hiloRetorno[14];         //Valor de retorno.

    settextstyle(4, 0, 3);
    outtextxy(MLX, MNY/3, (char *)"Algoritmos De Ordenamiento");

    //Imprimir los nombres y los elementos.
    for(i = 0; i < 7; i++)
    {
        settextstyle(4, 0, 1);
        outtextxy(MNX, MNY+i*INT, (char *)sorts[i]);

        for(j = 0; j < N; j++)
        {
            objeto(MLX+j*ESP, MLY+i*INT, lista[j]);
        }
    }
/*
    //Usado para probar que los algoritmos sirven, uno por uno.
    int v = 0;
    hiloRetorno[v] = pthread_create(&hiloID[v], NULL, menu, &v);
    hiloRetorno[v+7] = pthread_create(&hiloID[v+7], NULL, ordenamiento, &v);
    pthread_join(hiloID[v], NULL);
    pthread_join(hiloID[v+7], NULL);
*/
    //Creación de hilos: algoritmos.
    for (i = 0; i < 7; i++)
    {
        hiloRetorno[i] = pthread_create(&hiloID[i], NULL, menu, &sortID[i]);
    }

    //Creación de hilos: parte gráfica.
    for (i = 0; i < 7; i++)
    {
        hiloRetorno[i+7] = pthread_create(&hiloID[i+7], NULL, ordenamiento, &sortID[i]);
    }

    //Esperar a que todos los hilos terminen: algoritmos.
    for (i = 0; i < 7; i++)
    {
        pthread_join(hiloID[i], NULL);
    }

    //Esperar a que todos los hilos terminen: parte gráfica.
    for (i = 0; i < 7; i++)
    {
        pthread_join(hiloID[i+7], NULL);
    }

    //Destruir los mutex.
    for (i = 0; i < 7; i++)
    {
        pthread_mutex_destroy(&mutex[7]);
    }

    setcolor(WHITE);
    settextstyle(4, 0, 4);
    outtextxy(600, 500, (char *)"--FIN--");

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
    int i, j;                   //Contadores.
    int listaOrd[N];            //Para ordenar la lista.
    struct Parametros param;    //Para la cola de mensajes.

    for(i = 0; i < N; i++)
    {
        listaOrd[i] = lista[i];
    }

    //Recorre el arreglo.
    for(i = 1; i < N; i++)
    {
        //Compara dos elementos.
        for(j = 0; j < N - i; j++)
        {
            //Si están desordeados, los intercambia.
            if(listaOrd[j] > listaOrd[j+1])
            {
                //Ordenar los elementos en el arreglo.
                swap(listaOrd[j], listaOrd[j+1]);

                //Meter los elementos desordenados en la cola.
                pthread_mutex_lock(&mutex[id]);

                param = {j, j+1, listaOrd[j], listaOrd[j+1]};
                cola[id].push(param);

                pthread_mutex_unlock(&mutex[id]);
            }
        }
    }
}

//Hace un Bubble Sort de izquierda a derecha y otro de derecha a izquierda, repetir hasta ordenar todo.
void cocktailSort(int id)
{
    int i, j;                   //Contadores.
    int listaOrd[N];            //Para ordenar la lista.
    struct Parametros param;    //Para la cola de mensajes.
    int sw;                     //Para para indicar el fin de una ronda.

    for(i = 0; i < N; i++)
    {
        listaOrd[i] = lista[i];
    }

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
                swap(listaOrd[j+1], listaOrd[j]);

                pthread_mutex_lock(&mutex[id]);

                param = {j, j+1, listaOrd[j], listaOrd[j+1]};
                cola[id].push(param);

                pthread_mutex_unlock(&mutex[id]);
            }
        }

        //Bubble Sort de derecha a izquierda.
        for(j = 0; j < N - 1 - i; j++)
        {
            if(listaOrd[N-1-j] < listaOrd[N-2-j])
            {
                swap(listaOrd[N-2-j], listaOrd[N-1-j]);

                pthread_mutex_lock(&mutex[id]);

                param = {N-2-j, N-1-j, listaOrd[N-2-j], listaOrd[N-1-j]};
                cola[id].push(param);

                pthread_mutex_unlock(&mutex[id]);

                sw = 1;
            }
        }
    }
}

//Compara n con los elementos < n y lo coloca en donde corresponde, n++, repetir hasta ordenar todo.
void insertionSort(int id)
{
    int i, j;                   //Contadores.
    int listaOrd[N];            //Para ordenar la lista.
    struct Parametros param;    //Para la cola de mensajes.

    for(i = 0; i < N; i++)
    {
        listaOrd[i] = lista[i];
    }

    //Para recorrer el arreglo.
    for (i = 1 ; i <= N - 1; i++)
    {
        j = i;
        //Compara y ordena dos elementos, luego hace lo mismo con los elementos anteriores.
        while (j > 0 && listaOrd[j] < listaOrd[j-1])
        {
            //Ordenar los elementos en el arreglo.
            swap(listaOrd[j], listaOrd[j-1]);

            //Meter los elementos desordenados en la cola.
            pthread_mutex_lock(&mutex[id]);

            param = {j-1, j, listaOrd[j-1], listaOrd[j]};
            cola[id].push(param);

            pthread_mutex_unlock(&mutex[id]);

            j--;
        }
    }
}

//Aplica Bubble Sort a un número par e impar de parejas, repetir hasta ordenar todo.
void oddevenSort(int id)
{
    int i;                      //Contador.
    int listaOrd[N];            //Para ordenar la lista.
    struct Parametros param;    //Para la cola de mensajes.
    bool isSorted = false;      //Control del bucle.

    for(i = 0; i < N; i++)
    {
        listaOrd[i] = lista[i];
    }

    while (!isSorted)
    {
        isSorted = true;

        //Bubble Sort para el número impar de parejas.
        for (i=1; i<=N-2; i=i+2)
        {
            if (listaOrd[i] > listaOrd[i+1])
            {
                swap(listaOrd[i+1], listaOrd[i]);

                pthread_mutex_lock(&mutex[id]);

                param = {i, i+1, listaOrd[i], listaOrd[i+1]};
                cola[id].push(param);

                pthread_mutex_unlock(&mutex[id]);

                isSorted = false;
              }
        }

        //Bubble Sort para número par de parejas.
        for (int i=0; i<=N-2; i=i+2)
        {
            if (listaOrd[i] > listaOrd[i+1])
            {
                swap(listaOrd[i+1], listaOrd[i]);

                pthread_mutex_lock(&mutex[id]);

                param = {i, i+1, listaOrd[i], listaOrd[i+1]};
                cola[id].push(param);

                pthread_mutex_unlock(&mutex[id]);

                isSorted = false;
            }
        }
    }
}

//Compara n con los elementos > n para determinar el menor e intercambiar, repetir hasta ordenar todo.
void selectionSort(int id)
{
    int i, j;                   //Contadores.
    int listaOrd[N];            //Para ordenar la lista.
    struct Parametros param;    //Para la cola de mensajes.
    int amin, imin;             //Para valores mínimos.

    for(i = 0; i < N; i++)
    {
        listaOrd[i] = lista[i];
    }

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
            //Ordenar los elementos en el arreglo.
            swap(listaOrd[i], listaOrd[imin]);

            //Meter los elementos desordenados en la cola.
            pthread_mutex_lock(&mutex[id]);

            param = {i, imin, listaOrd[i], listaOrd[imin]};
            cola[id].push(param);

            pthread_mutex_unlock(&mutex[id]);
        }
    }
}

//Compara y ordena n y m distanciados por un gap, gap se reduce, repetir hasta ordenar todo.
void combSort(int id)
{
    int i, j;                   //Contadores.
    int listaOrd[N];            //Para ordenar la lista.
    struct Parametros param;    //Para la cola de mensajes.
    int gap = N;                //Gap inicial.
    bool swapped;               //Control para el bucle.

    for(i = 0; i < N; i++)
    {
        listaOrd[i] = lista[i];
    }

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
                //Ordenar los elementos en el arreglo.
                swap(listaOrd[i], listaOrd[i + gap]);

                //Meter los elementos desordenados en la cola.
                pthread_mutex_lock(&mutex[id]);

                param = {i, j, listaOrd[i], listaOrd[j]};
                cola[id].push(param);

                pthread_mutex_unlock(&mutex[id]);

                swapped = true;
            }
        }

        //Se sale del bucle cuando termina de ordenar.
        if (gap == 1 && !swapped)
            break;
    }
}

//Compara y ordena elementos alejados entre sí, reduce la lejanía, repetir hasta ordenar todo.
void shellSort(int id)
{
    int i, j, m;                //Contadores.
    int listaOrd[N];            //Para ordenar la lista.
    struct Parametros param;    //Para la cola de mensajes.

    for(i = 0; i < N; i++)
    {
        listaOrd[i] = lista[i];
    }

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
                    //Ordenar los elementos en el arreglo.
                    swap(listaOrd[i], listaOrd[i+m]);

                    //Meter los elementos desordenados en la cola.
                    pthread_mutex_lock(&mutex[id]);

                    param = {i, i+m, listaOrd[i], listaOrd[i+m]};
                    cola[id].push(param);

                    pthread_mutex_unlock(&mutex[id]);
                }
            }
        }
    }
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

//Toma mensajes de la cola para ordenar en la parte gráfica..
void *ordenamiento(void *ID)
{
    int *id = (int *)ID;

    cronometro[*id] = clock();   //Inicia el cronómetro.

    while (cola[*id].size() > 0)
    {
        pthread_mutex_lock(&mutex[*id]);

        struct Parametros param = cola[*id].front();
        int inIzq = param.inIzq;
        int inDer = param.inDer;
        int valIzq = param.valIzq;
        int valDer = param.valDer;

        cola[*id].pop();

        setcolor(GREEN);
        objeto(MOX+inDer*ESP, MLY+(*id)*INT, valDer);
        objeto(MOX+inIzq*ESP, MLY+(*id)*INT, valIzq);
        setcolor(BLACK);
        objeto(MOX+inDer*ESP, MLY+(*id)*INT, valDer);
        objeto(MOX+inIzq*ESP, MLY+(*id)*INT, valIzq);
        setcolor(GREEN);
        objeto(MOX+inDer*ESP, MLY+(*id)*INT, valDer);
        objeto(MOX+inIzq*ESP, MLY+(*id)*INT, valIzq);

        pthread_mutex_unlock(&mutex[*id]);
    }

    //Detiene el cronómetro e imprime el tiempo.
    cronometro[*id] = clock() - cronometro[*id];
    tiempo[*id] = ((double)cronometro[*id])/CLOCKS_PER_SEC;
    sprintf(T[*id], "%0.2f s", tiempo[*id]);
    setcolor(BLUE);
    settextstyle(0, 0, 2);
    outtextxy(MOX+N*ESP, MLY+(*id)*INT, T[*id]);
}

//Crea los objetos de la parte gráfica.
void objeto(int x, int y, int num)
{
    char dato[8];
    sprintf(dato, "%d", num);
    circle(x, y, 15);
    settextstyle(0, 0, 2);
    outtextxy(x-5, y-9, dato);
}
