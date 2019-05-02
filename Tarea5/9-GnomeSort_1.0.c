#include<stdio.h>
#include<conio.h>

/*
Algoritmo Gnome Sort.
Tomado de:
http://www.ccodechamp.com/c-program-of-gnome-sort-algorithm-c-code-champ/
https://www.geeksforgeeks.org/gnome-sort-a-stupid-one/
*/

void gnome_sort(int a[], int n)
{
    int i = 1, j = 2, t;

    //# define swap(i, j) { t = a[i]; a[i] = a[j]; a[j] = t; }
    while(i < n)
    {/*
        if (a[i - 1] > a[i]) {
        swap(i - 1, i);
        if (--i) continue;
        }
        i = j++;*/
        if (i == 0)
            i++;
        if (a[i] >= a[i - 1])
            i++;
        else {
            t = a[i];
            a[i] = a[i - 1];
            a[i - 1] = t;
            i--;
        }
    //# undef swap
    }
}

int main()
{
    int n, i, k = 0, A[15];

    printf("-----------------------------------------------------------\n");
    printf("----------------------Made by C code champ-----------------\n");
    printf("-----------------------------------------------------------\n\n");
    printf("\t\tGNOME SORT ALGORITHM\n\n\n\n");

    printf("Enter the number of input : ");
    scanf("%d",&n);

    printf("\n\nEnter the elements to be sorted :\n");
    for ( i = 0; i < n; i++)
    {
         scanf("%d", &A[i]);
    }

    gnome_sort(A,n);

    printf("\n\nSorted List by Gnome Sort :\n");
    for (i = 0; i < n; i++)
    {
         printf("%d\t", A[i]);
    }

    return 0;
}
