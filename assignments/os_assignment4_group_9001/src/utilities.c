#include "utilities.h"

void mergeSort(int arr[], int l, int r);
void merge(int arr[], int l, int m, int r);
int binarySearch(int arr[], int l, int r, int x);

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

int find(int* array, int len, int value) // Assumes array in ascending order
{
    int pos = binarySearch(array, 0, len - 1, value);
    if (pos < 0)
        return 0;
    else
    {
        int count = 1;
        for (int i = pos + 1; array[i] == value && i < len; i++)
            count++;
        for (int i = pos - 1; array[i] == value && i >= 0; i--)
            count++;
        return count;
    }
}

int binarySearch(int arr[], int l, int r, int x)
{
    if (r >= l) 
    {
        int mid = l + (r - l) / 2;

        if (arr[mid] == x)
            return mid;

        if (arr[mid] > x)
            return binarySearch(arr, l, mid - 1, x);

        return binarySearch(arr, mid + 1, r, x);
    }

    return -1;
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l+(r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
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
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
