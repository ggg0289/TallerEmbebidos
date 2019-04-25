#include<stdio.h>

/*
Algoritmo Insertion Sort.
Tomado de: http://www.ccodechamp.com/c-program-for-insertion-sort-algorithm/
*/

int main()
{
    int i, n, array[20], c, d, t;

    printf("-----------------------------------------------------------\n");
    printf("----------------------Made by C code champ-----------------\n");
    printf("-----------------------------------------------------------\n\n");
    printf("\t\tINSERTION SORT ALGORITHM\n\n\n\n");

    printf("Enter the number of input : ");
    scanf("%d", &n);

    printf("\n\nEnter the elements to be sorted :\n");
    for ( i = 0; i < n; i++)
    {
         scanf("%d", &array[i]);
    }

    for (c = 1 ; c <= n - 1; c++)
    {
        d = c;

        while (d > 0 && array[d] < array[d-1])
        {
            t = array[d];
            array[d] = array[d-1];
            array[d-1] = t;
            d--;
        }
    }

    printf("\n\nSorted List by Insertion Sort :\n");
    for (i = 0; i < n; i++)
    {
         printf("%d\t", array[i]);
    }

    return 0;
}
