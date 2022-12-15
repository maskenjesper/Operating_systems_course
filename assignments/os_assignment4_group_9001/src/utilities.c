#include "utilities.h"
#include <stdlib.h>

void mergeSort(int arr[], int l, int r);
void merge(int arr[], int l, int m, int r);

void errExit(const char *cause) 
{
    fprintf(stderr, "Failure! cause: %s\nerrno: %s(%d)\n",
            cause, strerror(errno), errno);
    exit(EXIT_FAILURE);
}

void printArray(int* array, int len) 
{
    for (int i = 0; i < len; i++)
        printf("%d ", array[i]);
    printf("\n");
}

int* copyArray(int* array, int len) // Remember to free
{
    int* outArr = malloc(len * sizeof(int));
    for (int i = 0; i < len; i++)
        outArr[i] = array[i];
    return outArr;
}

void sort(int* array, int len)
{
    mergeSort(array, 0, len - 1);
}

int find(int* array, int len, int value)
{
    sort(array, len);
    int lo = 0, hi = len - 1;
    while (lo + 5 < hi) {
        int mid = (hi - lo) / 2 + lo;
        if (value < array[mid])
            hi = mid - 1;
        else if (value > array[mid])
            lo = mid + 1;
        else
            return 1;
    }
    while (lo <= hi)
        if (value == array[lo++])
            return 1;
    return 0;
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        // Finding mid element
        int m = l+(r-l)/2;
        // Recursively sorting both the halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        // Merge the array
        merge(arr, l, m, r);
    }
}

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    // Create temp arrays
    int L[n1], R[n2];
    // Copy data to temp array
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
    // Merge the temp arrays
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    // Copy the remaining elements of L[]
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    // Copy the remaining elements of R[]
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
