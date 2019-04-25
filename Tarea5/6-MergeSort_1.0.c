#include<stdio.h>

/*
Algoritmo Merge Sort.
Tomado de: http://www.ccodechamp.com/c-program-of-merge-sort-algorithm-c-code-champ/
*/

int a[50];
void merge(int, int, int);

void merge_sort(int low, int high)
{
    int mid;

    if(low <  high)
    {
        mid = (low + high)/2;
        merge_sort(low, mid);
        merge_sort(mid+1, high);
        merge(low, mid, high);
    }
}

void merge(int low, int mid, int high)
{
    int h, i, j, b[50], k;
    h = low;
    i = low;
    j = mid+1;

    while((h <= mid) && (j <= high))
    {
        if(a[h]<=a[j])
        {
            b[i] = a[h];
            h++;
        }
        else
        {
            b[i] = a[j];
            j++;
        }
        i++;
    }

    if(h > mid)
    {
        for(k = j; k <= high; k++)
        {
            b[i] = a[k];
            i++;
        }
    }
    else
    {
        for(k = h; k <= mid; k++)
        {
            b[i] = a[k];
            i++;
        }
    }

    for(k = low; k <= high; k++)
        a[k]=b[k];
}

int main()
{
    int num, i;

    printf("------------------------------------------------------------------\n");
    printf("---------------------- Made by C code champ ----------------------\n");
    printf("------------------------------------------------------------------\n\n");
    printf("\t\t\tMERGE SORT\n");

    printf("\nEnter the total numbers: ");
    scanf("%d", &num);

    printf("\nEnter %d numbers: \n", num);
    for(i = 1; i <= num; i++)
    {
        scanf("%d", &a[i]);
    }

    merge_sort(1,num);

    printf("\nSORTED ORDER: \n");
    for(i = 1; i <= num; i++)
        printf("\t%d", a[i]);

    return 0;
}
