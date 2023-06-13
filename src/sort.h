#ifndef _SORT_H_
#define _SORT_H_

void swap(int *xp, int *yp);
void printArray(int arr[], int size);
double benchSort(void (*sortFun)(int v[], int len), int arr[], int n);

void insertionSort(int arr[], int n);
void selectionSort(int arr[], int n);
void bubbleSort(int arr[], int n);
void quickSort(int arr[], int n);
void mergeSort(int arr[], int n);

#endif