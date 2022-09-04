#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void Shellsort(int n[], int size, int Incrmnt[], int numinc)
{
    int span = 0;
    for(int incr = 0; incr < numinc; incr++){
        span = Incrmnt[incr];
        for(int i = span; i < size; i++){
            if(n[i] < n[i-span])
                swap(&n[i],&n[i-span]);
        }
    }
    for(int i = 0; i < size-1; i++){
        if(n[i] > n[i+1])
            swap(&n[i],&n[i+1]);
    }
    return;
}

int main(void)
{
    int num[8] = {25,57,48,37,12,92,86,33};
    int span[3] = {5,3,1};
    int size = sizeof(num) / sizeof(num[0]);
    Shellsort(num,size,span,3);
    for(int i = 0; i < size; i++)
        printf("%d\n",num[i]);
    return 0;
}