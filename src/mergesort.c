#include "sort.h"
#include <stdlib.h>

void merge(int arr[], int left, int middle, int right) {
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    // Creating with dynamic memory because we don't know array size
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[middle + 1 + j];

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    // ALWAYS remember to free the memory!
    free(L);
    free(R);
}

void r_mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        r_mergeSort(arr, left, middle);
        r_mergeSort(arr, middle + 1, right);

        merge(arr, left, middle, right);
    }
}

void mergeSort(int arr[], int n) {
    r_mergeSort(arr, 0, n-1); // It's still recursive, but I've normalized the function call so it can be placed in arrays or structs.
}