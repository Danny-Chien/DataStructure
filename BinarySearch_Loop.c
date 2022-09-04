#include <stdio.h>
#include <stdlib.h>

int BinarySearch(int *arr, int size, int x)
{
    int low = 0, high = size - 1, mid;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (arr[mid] == x)
            break;
        if (x < arr[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }
    if (low > high)
        return -1;
    return mid;
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
    pos = BinarySearch(A, len, x);
    if (pos != -1)
        printf("The number %d is at A[%d].", x, pos);
    else
        printf("Cannot find the number %d", x);
    return 0;
}