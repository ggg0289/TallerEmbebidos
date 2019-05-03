#include<stdio.h>

/*
Algoritmo Shell Sort.
Tomado de: http://www.ccodechamp.com/c-program-of-shell-sort-algorithm-c-code-champ/
*/

void shellsort(int a[], int n)
{
    int j, i, k, m, mid;
    for(m = n/2; m > 0 ; m/=2)
    {
        for(j = m; j < n; j++)
        {
            for(i = j-m; i >= 0; i-=m)
            {
                if(a[i+m] >= a[i])
                    break;
                else
                {
                    mid = a[i];
                    a[i] = a[i+m];
                    a[i+m] = mid;
                }
            }
        }
    }
}

int main()
{
    int a[20], i, n;

    printf("-----------------------------------------------------------\n");
    printf("----------------------Made by C code champ-----------------\n");
    printf("-----------------------------------------------------------\n\n");
    printf("\t\tSHELL SORT ALGORITHM\n\n\n\n");

    printf("Enter total elements : ");
    scanf("%d", &n);

    printf("\nEnter %d Elements : ", n);
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    shellsort(a,n);

    printf("\n\n\nSorted list by Shell sort :\n ");
    for(i=0;i< n;i++)
        printf("%d\t",a[i]);
    return 0;
}
