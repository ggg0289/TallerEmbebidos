#include<stdio.h>
#define MAX 10

/*
Algoritmo Cocktail Sort.
Tomado de: http://www.ccodechamp.com/c-program-for-cocktail-sort-algorithm-c-code-champ/
*/

int main()
{
    int a[MAX], b[MAX];
    int n,  i,  j,  pass,   sw=1,   temp;

    printf("Enter the number of elements present.\n");
    scanf("%d", &n);

    printf("Enter the elements :\n");
    for(i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }

    printf("The array elements before sorting are\n");
    for(i = 0; i < n; i++)
    {
        printf("%d\t", a[i]);
    }

    printf("\nElements after Cocktail sort are\n");

    sw = 1;
    for(i = 0; i < n - 1 && sw == 1; i++)
    {
        sw = 0;
        for(j = 0; j < n - 1 - i; j++)
        {
            if(b[j] > b[j+1])
            {
                temp = b[j+1];
                b[j+1] = b[j];
                b[j] = temp;
                sw = 1;
            }

            if(b[n-1-j] < b[n-2-j])
            {
                temp = b[n-2-j];
                b[n-2-j] = b[n-1-j];
                b[n-1-j] = temp;
                sw = 1;
            }
        }
    }

    for(j = 0; j < n; j++)
    {
        printf("%d\t", b[j]);
    }

    printf("\n\n\n\tNo. of passes : %d\n", i);
    printf("\n\n******************************************************");
    printf("\n*********** Code written by Ccodechamp ***************");
    printf("\n******************************************************");
}
