#include<stdio.h>

/*
Algoritmo Bubble Sort.
Tomado de: http://www.ccodechamp.com/c-program-of-bubble-sort-algorithm-c-code-champs/
*/

int arr[20];
int n;
void get();       // This is
void Bubble();    // the prototype for the functions
void Show();

int main()
{
    printf("------------------------------------------------------------------\n");
    printf("---------------------- Made by C code champ ----------------------\n");
    printf("------------------------------------------------------------------\n\n");
    printf("- This Program Explains Sorting Using Bubble Sort Algorithm -\n\n");
    get();
    Bubble();
    Show();
}

void get()
{
    int i;

    while(1)
    {
        printf("Enter the size of the elements : ");
        scanf("%d", &n);

        if(n <= 20)
                break;
            else
                printf("\nSorry the maximum no of elements is 20\n\n");
    }

    printf("\n");
    printf("----------------------\n");
    printf("Enter the values \n");
    printf("----------------------\n\n");

    for(i = 0; i < n ; i++)
        scanf("%d", &arr[i]);
}

void Bubble()
{
    int i, j;

    for(i = 1; i < n; i++)
    {
        for(j = 0; j < n - i; j++)
        {
            if(arr[j] > arr[j+1])
            {      //for descending use "<"
                int t;
                t = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = t;

            }
        }
    }
}

void Show()
{
    int i;

    printf("\n");
    printf("-----------------------\n");
    printf("Sorted Array Elements\n");
    printf("-----------------------\n");

    for(i = 0 ; i < n; i++)
    {
        printf("%d\n", arr[i]);
    }
}
