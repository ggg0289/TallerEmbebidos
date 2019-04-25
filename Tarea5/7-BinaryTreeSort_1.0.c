#include <stdio.h>
#include <stdlib.h>

/*
Algoritmo Binary Tree Sort.
Tomado de: http://www.ccodechamp.com/c-program-for-binary-tree-sort-algorithm/
*/

struct btreenode
{
    struct btreenode *leftchild;
    int data;
    struct btreenode *rightchild;
};

void insert(struct btreenode **, int);
void inorder(struct btreenode *);

int main()
{
    struct btreenode *bt;
    int arr[20], arr1[20];
    int i, num, j ;
    bt = NULL ; //initialize the node

    printf("******** Binary tree sort Algorithm by Ccodechamp ***********\n" );
    printf("\n");

    printf("\nEnter the number of elements in the list : ");
    scanf("%d", &num);

    printf("\nEnter the elements to be sorted: \n");
    for(i = 0; i < num; i++)
    {
        scanf("%d", &arr[i]);
        arr1[i] = arr[i];
    }

    printf( "\nDisplay Array contents:\n" ) ;
    for (i = 0 ; i < num ; i++)
        printf("%d\t", arr[i]);

    for (j = 0 ; j < num ; j++)
        insert(&bt, arr1[j]);

    printf("\nIn-order traversal of binary tree:\n");
    inorder(bt);

    return 0;
}

void insert(struct btreenode **sr, int num1)
{
    if (*sr == NULL)
    {
        *sr = malloc(sizeof(struct btreenode));
        (*sr)->leftchild = NULL;
        (*sr)->data = num1;
        (*sr)->rightchild = NULL;
    }
    else
    {
        if (num1 < (*sr)->data)
            insert(&((*sr)->leftchild), num1);
        else
            insert(&((*sr)->rightchild), num1);
    }
}

void inorder(struct btreenode *sr)
{
    if (sr != NULL)
    {
        inorder(sr->leftchild) ;
        printf("%d\t", sr->data) ;
        inorder(sr->rightchild) ;
    }
}
