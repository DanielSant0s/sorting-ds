#include "sort.h"

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void r_quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        r_quickSort(arr, low, pi - 1);
        r_quickSort(arr, pi + 1, high);
    }
}

void quickSort(int arr[], int n) {
    r_quickSort(arr, 0, n-1); // It's still recursive, but I've normalized the function call so it can be placed in arrays or structs
}
