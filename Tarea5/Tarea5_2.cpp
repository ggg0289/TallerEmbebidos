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

#define D 0             //Para los delays, cuando se necesite visualizar.
#define MNX 25          //Margen en x para los nombres.
#define MNY 25          //Margen en y para los nombres.
#define MLX MNX+240     //Margen en x para los elementos iniciales.
#define MLY MNY+10      //Margen en y para los elementos iniciales.
#define MOX MLX         //Margen en x para los elementos a ordenar.
#define MOY MLY+50      //Margen en y para los elementos a ordenar.
#define MBY MOY+50      //Margen en y para los elementos a ordenar uando bajan.
#define ESP 50          //Espaciado enre elementos.
#define INT 100         //Interlineado.

int N;              //Número de elementos a ordenar.
int lista[50];     //Lista de elementos a ordenar.

//Para dibujar un círcuo con el número adentro.
class Elemento
{
    private:
        char dato[8];

    public:
        int x;
        int y;
        int num;
        void objeto();
};

//Para la parte gráfica del ordenamiento.
class Animacion
{
    private:
        int k;
        int COLOR;
        Elemento objA;

    public:
        int izq;
        int der;
        int listaOrd[50];
        int id;
        int dir;
        int ij[2];
        void ordenamiento();
};

void *menu(void *ID);
void bubbleSort(int id);
void cocktailSort(int id);
void insertionSort(int id);
void oddevenSort(int id);
void selectionSort(int id);
void combSort(int id);
void shellSort(int id);
int newGap(int gap);

int main()
{
    int i, j;              //Contadores para los for.
    Elemento objL;
    char sorts[7][25] =
    { "Bubble Sort",
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

    initwindow(getmaxwidth(), getmaxheight(), "ALGORITMOS DE ORDENAMIENTO - EJECUCIÓN");  //Iniciar graphics.

    //Arreglos para variables de los hilos.
    pthread_t hiloID[7];        //Identificador.
    int hiloRetorno[7];         //Valor de retorno.

    //Imprimir los nombres y los elementos.
    for(i = 0; i < 7; i++)
    {
        settextstyle(4, 0, 1);
        outtextxy(MNX, MNY+i*INT, (char *)sorts[i]);

        for(j = 0; j < N; j++)
        {
            objL.x = MLX+j*ESP;
            objL.y = MLY+i*INT;
            objL.num = lista[j];
            objL.objeto();

        }
    }
/*
    //Usado para probar que los algoritmos sirven, uno por uno.
    int v = 0;
    hiloRetorno[v] = pthread_create(&hiloID[v], NULL, menu, &v);
    pthread_join(hiloID[v], NULL);
*/
    //Creación de un hilo por algoritmo.
    for (i = 0; i < 7; i++)
    {
        hiloRetorno[i] = pthread_create(&hiloID[i], NULL, menu, &i);
    }

    //Esperar a que todos los hilos terminen.
    for (i = 0; i < 7; i++){
        pthread_join(hiloID[i], NULL);
    }

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
    int i, j;           //Contadores.
    int temp;           //Para almacenamiento temporal.
    Animacion animBS;   //Para la parte gráfica.

    //Para medir el tiempo de ejecución.
    clock_t cronometro;
    double tiempo;
    char T[8];

    for(i = 0; i < N; i++)
    {
        animBS.listaOrd[i] = lista[i];
    }

    cronometro = clock();   //Inicia el cronómetro.

    //Recorre el arreglo.
    for(i = 1; i < N; i++)
    {
        //Compara dos elementos.
        for(j = 0; j < N - i; j++)
        {
            //Si están desordeados, los intercambia.
            if(animBS.listaOrd[j] > animBS.listaOrd[j+1])
            {
                animBS.izq = j;
                animBS.der = j+1;
                animBS.id = id;
                animBS.dir = 0;
                animBS.ij[0] = 0;
                animBS.ij[1] = 0;
                animBS.ordenamiento();

                //Para la parte de arreglos.
                temp = animBS.listaOrd[j];
                animBS.listaOrd[j] = animBS.listaOrd[j+1];
                animBS.listaOrd[j+1] = temp;
            }
        }
    }

    //Detiene el cronómetro e imprime el tiempo.
    cronometro = clock() - cronometro;
    tiempo = ((double)cronometro)/CLOCKS_PER_SEC;
    sprintf(T, "%0.2f s", tiempo);
    settextstyle(0, 0, 2);
    outtextxy(MOX+N*ESP, MLY+id*INT, T);
}

//Hace un Bubble Sort de izquierda a derecha y otro de derecha a izquierda, repetir hasta ordenar todo.
void cocktailSort(int id)
{
    int i, j;           //Contadores.
    int temp;           //Para almacenamiento temporal.
    int sw;             //Para para indicar el fin de una ronda.
    Animacion animCS;   //Para la parte gráfica.

    //Para medir el tiempo de ejecución.
    clock_t cronometro;
    double tiempo;
    char T[8];

    for(i = 0; i < N; i++)
    {
        animCS.listaOrd[i] = lista[i];
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
            if(animCS.listaOrd[j] > animCS.listaOrd[j+1])
            {
                animCS.izq = j;
                animCS.der = j+1;
                animCS.id = id;
                animCS.dir = 0;
                animCS.ij[0] = 0;
                animCS.ij[1] = 0;
                animCS.ordenamiento();

                temp = animCS.listaOrd[j+1];
                animCS.listaOrd[j+1] = animCS.listaOrd[j];
                animCS.listaOrd[j] = temp;
            }
        }

        //Bubble Sort de derecha a izquierda.
        for(j = 0; j < N - 1 - i; j++)
        {
            if(animCS.listaOrd[N-1-j] < animCS.listaOrd[N-2-j])
            {
                animCS.izq = N-2-j;
                animCS.der = N-1-j;
                animCS.id = id;
                animCS.dir = 1;
                animCS.ij[0] = 0;
                animCS.ij[1] = 0;
                animCS.ordenamiento();

                temp = animCS.listaOrd[N-2-j];
                animCS.listaOrd[N-2-j] = animCS.listaOrd[N-1-j];
                animCS.listaOrd[N-1-j] = temp;
                sw = 1;
            }
        }
    }

    //Detiene el cronómetro e imprime el tiempo.
    cronometro = clock() - cronometro;
    tiempo = ((double)cronometro)/CLOCKS_PER_SEC;
    sprintf(T, "%0.2f s", tiempo);
    settextstyle(0, 0, 2);
    outtextxy(MOX+N*ESP, MLY+id*INT, T);
}

//Compara n con los elementos < n y lo coloca en donde corresponde, n++, repetir hasta ordenar todo.
void insertionSort(int id)
{
    int i,  j, k;       //Contadores.
    int temp;           //Para almacenamiento temporal.
    Animacion animIS;   //Para la parte gráfica.

    //Para medir el tiempo de ejecución.
    clock_t cronometro;
    double tiempo;
    char T[8];

    for(i = 0; i < N; i++)
    {
        animIS.listaOrd[i] = lista[i];
    }

    cronometro = clock();   //Inicia el cronómetro.

    //Para recorrer el arreglo.
    for (i = 1 ; i <= N - 1; i++)
    {
        j = i;
        //Compara y ordena dos elementos, luego hace lo mismo con los elementos anteriores.
        while (j > 0 && animIS.listaOrd[j] < animIS.listaOrd[j-1])
        {
            animIS.izq = j-1;
            animIS.der = j;
            animIS.id = id;
            animIS.dir = 0;
            animIS.ij[0] = i;
            animIS.ij[1] = j;
            animIS.ordenamiento();

            //Para la parte de arreglos.
            temp = animIS.listaOrd[j];
            animIS.listaOrd[j] = animIS.listaOrd[j-1];
            animIS.listaOrd[j-1] = temp;
            j--;
        }
    }

    //Detiene el cronómetro e imprime el tiempo.
    cronometro = clock() - cronometro;
    tiempo = ((double)cronometro)/CLOCKS_PER_SEC;
    sprintf(T, "%0.2f s", tiempo);
    settextstyle(0, 0, 2);
    outtextxy(MOX+N*ESP, MLY+id*INT, T);
}

//Aplica Bubble Sort a un número par e impar de parejas, repetir hasta ordenar todo.
void oddevenSort(int id)
{
    int i, k;               //Contadores.
    int temp;               //Para almacenamiento temporal.
    bool isSorted = false;  //Control del bucle.
    Animacion animOES;      //Para la parte gráfica.

    //Para medir el tiempo de ejecución.
    clock_t cronometro;
    double tiempo;
    char T[8];

    for(i = 0; i < N; i++)
    {
        animOES.listaOrd[i] = lista[i];
    }

    cronometro = clock();   //Inicia el cronómetro.

    while (!isSorted)
    {
        isSorted = true;

        //Bubble Sort para el número impar de parejas.
        for (i=1; i<=N-2; i=i+2)
        {
            if (animOES.listaOrd[i] > animOES.listaOrd[i+1])
            {
                animOES.izq = i;
                animOES.der = i+1;
                animOES.id = id;
                animOES.dir = 0;
                animOES.ij[0] = 0;
                animOES.ij[1] = 0;
                animOES.ordenamiento();

                temp = animOES.listaOrd[i+1];
                animOES.listaOrd[i+1] = animOES.listaOrd[i];
                animOES.listaOrd[i] = temp;
                isSorted = false;
              }
        }

        //Bubble Sort para número par de parejas.
        for (int i=0; i<=N-2; i=i+2)
        {
            if (animOES.listaOrd[i] > animOES.listaOrd[i+1])
            {
                animOES.izq = i;
                animOES.der = i+1;
                animOES.id = id;
                animOES.dir = 1;
                animOES.ij[0] = 0;
                animOES.ij[1] = 0;
                animOES.ordenamiento();

                temp = animOES.listaOrd[i+1];
                animOES.listaOrd[i+1] = animOES.listaOrd[i];
                animOES.listaOrd[i] = temp;
                isSorted = false;
            }
        }
    }

    //Detiene el cronómetro e imprime el tiempo.
    cronometro = clock() - cronometro;
    tiempo = ((double)cronometro)/CLOCKS_PER_SEC;
    sprintf(T, "%0.2f s", tiempo);
    settextstyle(0, 0, 2);
    outtextxy(MOX+N*ESP, MLY+id*INT, T);
}

//Compara n con los elementos > n para determinar el menor e intercambiar, repetir hasta ordenar todo.
void selectionSort(int id)
{
    int i,  j, k;       //Contadores.
    int temp;           //Para almacenamiento temporal.
    int amin, imin;     //Para valores mínimos.
    Animacion animSS;   //Para la parte gráfica.

    //Para medir el tiempo de ejecución.
    clock_t cronometro;
    double tiempo;
    char T[8];

    for(i = 0; i < N; i++)
    {
        animSS.listaOrd[i] = lista[i];
    }

    cronometro = clock();   //Inicia el cronómetro.

    //Para recorrer el arreglo.
    for(i = 0; i <= N-1; i++)
    {
        //Presuntos valores mínimos.
        imin = i;
        amin = animSS.listaOrd[i];

        //Para compararlos con los valores posteriores.
        for(j = i+1; j <= N-1; j++)
        {
            //Para asegurar de que siempre se guarde el menor.
            if(animSS.listaOrd[j] < amin)
            {
                imin = j;
                amin = animSS.listaOrd[j];
            }
        }

        //Hace el intercambio.
        if(imin != 1)
        {
            animSS.izq = i;
            animSS.der = imin;
            animSS.id = id;
            animSS.dir = 0;
            animSS.ij[0] = 0;
            animSS.ij[1] = 0;
            animSS.ordenamiento();

            //Para la parte de arreglos.
            temp = animSS.listaOrd[i];
            animSS.listaOrd[i] = animSS.listaOrd[imin];
            animSS.listaOrd[imin] = temp;
        }
    }

    //Detiene el cronómetro e imprime el tiempo.
    cronometro = clock() - cronometro;
    tiempo = ((double)cronometro)/CLOCKS_PER_SEC;
    sprintf(T, "%0.2f s", tiempo);
    settextstyle(0, 0, 2);
    outtextxy(MOX+N*ESP, MLY+id*INT, T);
}

//Compara y ordena n y m distanciados por un gap, gap se reduce, repetir hasta ordenar todo.
void combSort(int id)
{
    int i,  j, k;       //Contadores.
    int temp;           //Para almacenamiento temporal.
    int gap = N;        //Gap inicial.
    bool swapped;       //Control para el bucle.
    Animacion animCoS;   //Para la parte gráfica.

    //Para medir el tiempo de ejecución.
    clock_t cronometro;
    double tiempo;
    char T[8];

    for(i = 0; i < N; i++)
    {
        animCoS.listaOrd[i] = lista[i];
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
            if (animCoS.listaOrd[i] > animCoS.listaOrd[j])
            {

                animCoS.izq = i;
                animCoS.der = j;
                animCoS.id = id;
                animCoS.dir = 0;
                animCoS.ij[0] = 0;
                animCoS.ij[1] = 0;
                animCoS.ordenamiento();

                //Para la parte de arreglos.
                temp = animCoS.listaOrd[i];
                animCoS.listaOrd[i] = animCoS.listaOrd[i + gap];
                animCoS.listaOrd[i + gap] = temp;
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
    outtextxy(MOX+N*ESP, MLY+id*INT, T);
}

//Compara y ordena elementos alejados entre sí, reduce la lejanía, repetir hasta ordenar todo.
void shellSort(int id)
{
    int i, j, k, m;     //Contadores.
    int temp;           //Para almacenamiento temporal.
    Animacion animShS;   //Para la parte gráfica.

    //Para medir el tiempo de ejecución.
    clock_t cronometro;
    double tiempo;
    char T[8];

    for(i = 0; i < N; i++)
    {
        animShS.listaOrd[i] = lista[i];
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
                if(animShS.listaOrd[i+m] >= animShS.listaOrd[i])
                    break;
                else
                {
                    animShS.izq = i;
                    animShS.der = i+m;
                    animShS.id = id;
                    animShS.dir = 0;
                    animShS.ij[0] = 0;
                    animShS.ij[1] = 0;
                    animShS.ordenamiento();

                    temp = animShS.listaOrd[i];
                    animShS.listaOrd[i] = animShS.listaOrd[i+m];
                    animShS.listaOrd[i+m] = temp;
                }
            }
        }
    }

    //Detiene el cronómetro e imprime el tiempo.
    cronometro = clock() - cronometro;
    tiempo = ((double)cronometro)/CLOCKS_PER_SEC;
    sprintf(T, "%0.2f s", tiempo);
    settextstyle(0, 0, 2);
    outtextxy(MOX+N*ESP, MLY+id*INT, T);
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
void Animacion::ordenamiento()
{
    //Para Cocktail y Odd-Even.
    if(dir == 0)
    {
        COLOR = GREEN;
    }
    else
    {
        COLOR = RED;
    }
    //Bajar.
    for(k = 0; k < ESP; k++)
    {
        //Para Insertion, Selection, Comb, Shell.
        if (id == 2 || id == 4 || id == 5 || id == 6)
        {
            //El primer elemento siempre es azul.
            if (ij[1] == ij[0])
            {
                setcolor(BLUE);
            }
            else
            {
                setcolor(WHITE);
            }
            //Anterior/Presunto menor/Primero/Primero.
            objA.x = MOX+der*ESP;
            objA.y = MLY+id*INT;
            objA.num = listaOrd[der];
            objA.objeto();
            setcolor(RED);
            //Presente/Verdadero menor/Separado/Distanciado.
            objA.x = MOX+izq*ESP;
            objA.y = MLY+id*INT;
            objA.num = listaOrd[izq];
            objA.objeto();
        }

        setcolor(COLOR);
        objA.x = MOX+izq*ESP;
        objA.y = MLY+id*INT+k;
        objA.num = listaOrd[izq];
        objA.objeto();
        delay(D);
        setcolor(BLACK);
        objA.x = MOX+izq*ESP;
        objA.y = MLY+id*INT+k;
        objA.num = listaOrd[izq];
        objA.objeto();

        setcolor(COLOR);
        objA.x = MOX+der*ESP;
        objA.y = MLY+id*INT+k;
        objA.num = listaOrd[der];
        objA.objeto();
        delay(D);
        setcolor(BLACK);
        objA.x = MOX+der*ESP;
        objA.y = MLY+id*INT+k;
        objA.num = listaOrd[der];
        objA.objeto();
    }

    setcolor(WHITE);
    objA.x = MOX+izq*ESP;
    objA.y = MLY+id*INT+k;
    objA.num = listaOrd[izq];
    objA.objeto();
    objA.x = MOX+der*ESP;
    objA.y = MLY+id*INT+k;
    objA.num = listaOrd[der];
    objA.objeto();

    //Intercambiar.
    for(k = 0; k < (der - izq)*ESP; k++)
    {
        setcolor(COLOR);
        objA.x = MOX+izq*ESP+k;
        objA.y = MOY+id*INT;
        objA.num = listaOrd[izq];
        objA.objeto();
        objA.x = MOX+der*ESP-k;
        objA.y = MOY+id*INT;
        objA.num = listaOrd[der];
        objA.objeto();
        delay(D);
        setcolor(BLACK);
        objA.x = MOX+izq*ESP+k;
        objA.y = MOY+id*INT;
        objA.num = listaOrd[izq];
        objA.objeto();
        objA.x = MOX+der*ESP-k;
        objA.y = MOY+id*INT;
        objA.num = listaOrd[der];
        objA.objeto();
    }

    setcolor(WHITE);
    objA.x = MOX+izq*ESP+k;
    objA.y = MOY+id*INT;
    objA.num = listaOrd[izq];
    objA.objeto();
    objA.x = MOX+der*ESP-k;
    objA.y = MOY+id*INT;
    objA.num = listaOrd[der];
    objA.objeto();

    //Subir.
    for(k = ESP; k > 0; k--)
    {
        setcolor(COLOR);
        objA.x = MOX+izq*ESP;
        objA.y = MLY+id*INT+k;
        objA.num = listaOrd[der];
        objA.objeto();
        delay(D);
        setcolor(BLACK);
        objA.x = MOX+izq*ESP;
        objA.y = MLY+id*INT+k;
        objA.num = listaOrd[der];
        objA.objeto();

        setcolor(COLOR);
        objA.x = MOX+der*ESP;
        objA.y = MLY+id*INT+k;
        objA.num = listaOrd[izq];
        objA.objeto();
        delay(D);
        setcolor(BLACK);
        objA.x = MOX+der*ESP;
        objA.y = MLY+id*INT+k;
        objA.num = listaOrd[izq];
        objA.objeto();
    }

    setcolor(WHITE);
    objA.x = MOX+izq*ESP;
    objA.y = MLY+id*INT+k;
    objA.num = listaOrd[der];
    objA.objeto();
    objA.x = MOX+der*ESP;
    objA.y = MLY+id*INT+k;
    objA.num = listaOrd[izq];
    objA.objeto();

}

//Crea los objetos de la parte gráfica.
void Elemento::objeto()
{
    sprintf(dato, "%d", num);
    circle(x, y, 15);
    settextstyle(0, 0, 2);
    outtextxy(x-5, y-9, dato);
}
