#include <stdlib.h>
#include <stdio.h>

/*
    Summary:
        Heapsort -> data become tree 
                 -> using Adjust() to make sure every father in tree are bigger than son
                 -> using Maxremove() to sort the tree
                 -> time complexty is O(nlogn)
*/

void swap(int *a, int *b)
{
    int temp = *b;
    *b = *a;
    *a = temp;
    return;
}

void Adjust(int n[], int lb, int up)
{
    /* lb -> the last father, j -> the left son of the last father */
    int tmp = n[lb], j = (2 * lb) + 1;
    while(j <= up){
        if((j < up) && (n[j] < n[j+1]))
            j++;    /* index moves to right son(bigger than left son) */
        /* father is bigger than the right son */
        if(tmp >= n[j]){
            n[(j-1)/2] = tmp;
            break;
        }

        /* father is smaller than son */
        int value = n[(j-1)/2];
        n[(j-1)/2] = n[j];
        n[j] = value;
        j = (2 * j) + 1;
    }

    return;
}

void Maxremove(int n[], int size)
{
    for(int i = (size - 2); i >= 0; i--){
        swap(&n[0],&n[i+1]);    /* everytime let the biggest number go tothe last one */
        Adjust(n,0,i);  /* sort without the biggest number*/
    }

    return;
}

int main(void)
{
    int num[10] = {26,5,77,1,61,11,59,15,48,19};
    int size = sizeof(num) / sizeof(num[0]);

    /* Construct Heapsort */
    for(int i = (size - 2)/2; i >= 0; i--){
        Adjust(num,i,(size - 1));
    }
    Maxremove(num,size);

    for(int i = 0; i < 10; i++)
        printf("%d\n",num[i]);

    return 0;
}