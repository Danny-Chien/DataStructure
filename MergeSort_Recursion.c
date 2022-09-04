#include <stdio.h>
#include <stdlib.h>


/**
*   list1 = {list1_begin, ..., list1_end}
*   list2 = {list2_begiin, ..., list2_end}
*   list2_begin = list1_end
*   range: [list1_begin, list1_end)
*/
void Merge_Subarray(int *arr, int list1_begin, int list1_end, int list2_end)
{
    int i = 0, j = list1_end, k = 0;
    int *tmp = malloc(sizeof(int) * list2_end);
    for (int z = 0; z < list1_end; z++)
        tmp[z] = arr[z];

    while (i < list1_end && j < list2_end)
    {
        if (tmp[i] < arr[j])
            arr[k++] = tmp[i++];
        else
            arr[k++] = arr[j++];
    }
    while (i < list1_end)
        arr[k++] = tmp[i++];
    while (j < list2_end)
        arr[k++] = arr[j++];
    free(tmp);
}

void MergeSort(int *arr, int m, int n)
{

    if (n - m != 1)
    {
        int middle = (m + n) / 2;
        MergeSort(arr, middle, n);
        MergeSort(arr, m, middle);
        Merge_Subarray(arr, m, middle, n);
    }
}

int main()
{
    int A[20];
    int len = sizeof(A) / sizeof(int);
    for (int i = 0; i < len; i++)
    {
        A[i] = (rand() % 100) + 1;
    }
    printf("Before Merge Sort:\n\t");
    for (int i = 0; i < len; i++)
    {
        printf("%d\t", A[i]);
    }
    printf("\nAfter Merge Sort:\n\t");
    MergeSort(A, 0, len);
    for (int i = 0; i < len; i++)
    {
        printf("%d\t", A[i]);
    }
}