#include<stdio.h>

/*
Algoritmo Selection Sort.
Tomado de: http://www.ccodechamp.com/c-program-for-selection-sort-algorithm-c-code-champs/
*/

int main()
{
    int a[100], n, i, j, temp, loc, min;
    printf("------------------------------------------------------------------\n");
    printf("---------------------- Made by C code champ ----------------------\n");
    printf("------------------------------------------------------------------\n\n");

    printf("\nEnter the number of elements : ");
    scanf("%d",&n);

    printf("Enter the element of array : \n");
    for(i = 0; i <= n-1; i++)
    {
        scanf("%d", &a[i]);
    }

    for(i = 0; i <= n-1; i++)
    {
        min = a[i];
        loc = i;

        for(j = i+1; j <= n-1; j++)
        {
            if(a[j] < min)
            {
                min = a[j];
                loc = j;
            }
        }

        if(loc != 1)
        {
            temp = a[i];
            a[i] = a[loc];
            a[loc] = temp;
        }
    }

    printf("The list of elements after applying selection sort :\n");
    for(i = 0; i <= n-1; i++)
    {
        printf("%d\t", a[i]);
    }

    return 0;
}
