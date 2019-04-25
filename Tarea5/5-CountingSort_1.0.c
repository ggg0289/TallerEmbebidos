#include <stdio.h>

/*
Algoritmo Counting Sort.
Tomado de: http://www.ccodechamp.com/c-program-for-counting-sort-algorithm/
*/

void counting_sort(int A[], int k, int n)
{
    int i, j;
    int B[n];  //Output
    int C[k]; //Contador

    for (i = 0; i <= k; i++)    //Inicializar contador en 0.
        C[i] = 0;

    for (j = 1; j <= n; j++)    //Calcular el número de cada elemento.
        C[A[j]] = C[A[j]] + 1;

    for (i = 1; i <= k; i++)    //Almacenar la posición de cada elemento.
        C[i] = C[i] + C[i-1];

    for (j = n; j >= 1; j--)    //Construir el output.
    {
        B[C[A[j]]] = A[j];
        C[A[j]] = C[A[j]] - 1;
    }

    printf("The Sorted array is : ");
    for (i = 1; i <= n; i++)
        printf("%d ", B[i]);
}

int main()
{
    int n, k = 0, A[15], i;

    printf("Enter the number of input : ");
    scanf("%d", &n);

    printf("\nEnter the elements to be sorted :\n");
    for (i = 1; i <= n; i++)
    {
        scanf("%d", &A[i]); //Obtener el rango.
        if (A[i] > k) {
            k = A[i];
        }
    }

    counting_sort(A, k, n);

    printf("\n");
    return 0;
}
