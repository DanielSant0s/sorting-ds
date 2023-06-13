#include <stdio.h>
#include <time.h>
#include "sort.h"

#define clock2sec(s, e) ((double)(e - s)) / CLOCKS_PER_SEC

void swap(int *xp, int *yp) {
    int tmp = *xp;
    *xp = *yp;
    *yp = tmp;
}

void printArray(int arr[], int size) {
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

double benchSort(void (*sortFun)(int v[], int len), int arr[], int n) {
    clock_t start, end;

    start = clock();
    sortFun(arr, n);
    end = clock();    

    return clock2sec(start, end);
}
