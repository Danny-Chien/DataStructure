#include <stdio.h>
#include <stdlib.h>

int BinarySearch(int *arr, int low, int high, int x)
{
    int mid;
    if (low > high)
        return -1;
    mid = (low + high) / 2;
    if (x == arr[mid])
        return mid;
    if (x < arr[mid])
        return BinarySearch(arr, low, mid - 1, x);
    else
        return BinarySearch(arr, mid + 1, high, x);
}

int main()
{
    int x, pos;
    int A[20];
    int len = sizeof(A) / sizeof(int);
    for (int i = 0; i < len; i++)
    {
        A[i] = (rand() % 100) + 1;
    }
    MergeSort(A, 0, len);
    for (int i = 0; i < len; i++)
    {
        printf("%d\t", A[i]);
    }
    printf("\nEnter a number you want to find:");
    scanf("%d", &x);
    pos = BinarySearch(A, 0, len, x);
    if (pos != -1)
        printf("The number %d is at A[%d].", x, pos);
    else
        printf("Cannot find the number %d", x);
    return 0;
}