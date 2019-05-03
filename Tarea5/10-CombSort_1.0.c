#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

/*
Algoritmo Comb Sort.
Tomado de: http://www.ccodechamp.com/c-program-for-comb-sort-algorithm-c-code-champ/
*/

int newGap(int gap)
{
    gap = (gap * 10) / 13;
    if (gap == 9 || gap == 10)
        gap = 11;
    if (gap < 1)
        gap = 1;
    return gap;
}

void combsort(int a[], int aSize)
{
    int gap = aSize;

    for (;;)
    {
        gap = newGap(gap);
        bool swapped = false;
        for (int i = 0; i < aSize - gap; i++)
        {
            int j = i + gap;
            if (a[i] > a[j])
            {
                int temp=a[i];
                a[i]=a[i + gap];
                a[i + gap]=temp;
                swapped = true;
            }
        }

    if (gap == 1 && !swapped)
        break;
    }
}

int main ()
{
    int n;
    int *a;

    printf("-----------------------------------------------------------\n");
    printf("----------------------Made by C code champ-----------------\n");
    printf("-----------------------------------------------------------\n\n");
    printf("\t\t\tCOMB SORT\n\n\n\n");

    printf("Please insert the number of elements to be sorted: ");
    scanf("%d",&n);       // The total number of elements

    a = (int *)calloc(n, sizeof(int));
    for(int i = 0; i < n; i++)
    {
        printf("Input %d element: ",i);
        scanf("%d",&a[i]); // Adding the elements to the array
    }

    printf("\n\n\nUnsorted list:\n");       // Displaying the unsorted array
    for(int i = 0; i < n; i++)
    {
        printf("%d\t",a[i]);
    }

    combsort(a, n);

    printf("\n\n\nSorted list:\n");        // Display the sorted array
    for(int i=0;i < n;i++)
    {
        printf("%d\t",a[i]);
    }

    return 0;
}
