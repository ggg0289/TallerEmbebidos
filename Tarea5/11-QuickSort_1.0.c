#include<stdio.h>

 /*
 Algoritmo Qick Sort.
 Tomado de: http://www.ccodechamp.com/c-program-for-quick-sort-algorithm/
 */

void quicksort(int arr[], int low, int high);

int main()
{
    int array[50] = {0};
    int i = 0,MAXARRAY;

    printf("\nEnter the number of elements :");
    scanf("%d",&MAXARRAY);
    printf("\nEnter the elements to be sorted : \n");
    for(i = 0; i < MAXARRAY; i++)
    {
        scanf("%d",&array[i]);
    }

    /* print the original array */
    printf("\nBefore quicksort:\n ");
    for(i = 0; i < MAXARRAY; i++)
    {
        printf(" %d ", array[i]);
    }
    printf("\n");

    quicksort(array, 0, (MAXARRAY - 1));

    /* print the `quicksorted' array */
    printf("\nAfter  quicksort:\n ");
    for(i = 0; i < MAXARRAY; i++)
    {
        printf(" %d ", array[i]);
    }

    printf("\n");
    printf("\n\n******************************************************");
    printf("\n*********** Code written by Ccodechamp ***************");
    printf("\n******************************************************");

    return 0;
}

/* sort everything inbetween `low' <-> `high' */
void quicksort(int arr[], int low, int high)
{
    int i = low;
    int j = high;
    int y = 0;
    /* compare value */
    int z = arr[(low + high) / 2];

    /* partition */
    do
    {
        /* find member above ... */
        while(arr[i] < z) i++;

        /* find element below ... */
        while(arr[j] > z) j--;

        if(i <= j)
        {
            /* swap two elements */
            y = arr[i];
            arr[i] = arr[j];
            arr[j] = y;
            i++;
            j--;
        }
    } while(i <= j);

    /* recurse */
    if(low < j)
        quicksort(arr, low, j);

    if(i < high)
        quicksort(arr, i, high);
}
