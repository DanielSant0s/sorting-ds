#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include "sort.h"

void (*sortFuncs[5])(int v[], int len) = {selectionSort, bubbleSort, insertionSort, mergeSort, quickSort};
const char* sortNames[5] = {"Selection", "Bubble", "Insertion", "Merge", "Quick"};

void benchAll(int arr[], int n) {
    double time_taken;
    int* tmp_arr = malloc(n*sizeof(int)); // Let's copy our array so we don't need to beckup it before
    memcpy(tmp_arr, arr, n*sizeof(int));

    for (int i = 0; i < 5; i++) {
        time_taken = benchSort(sortFuncs[i], tmp_arr, n);
        printf("%sSort: %f seconds\n", sortNames[i], time_taken);
        memcpy(tmp_arr, arr, n*sizeof(int));
    }

    free(tmp_arr);
}

// Creates an int array from a text file
int* readArrayFromFile(const char* filename, int* size) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error while opening %s.\n", filename);
        return NULL;
    }

    // Count non-empty lines
    int ch;
    *size = 0;
    while ((ch = fgetc(file)) != EOF) {
        
        if (ch == '\n') {
            (*size)++;
        }
    }
    
    rewind(file);

    int* array = (int*)malloc((*size) * sizeof(int));
    if (array == NULL) {
        printf("Error while allocating memory for the integer array.\n");
        fclose(file);
        return NULL;
    }

    // Read the values and put it on array slot
    for (int i = 0; i < *size; i++) {
        fscanf(file, "%d", &array[i]);
    }

    fclose(file);
    return array;
}

void benchFromFile(const char* path) {
    int *array, size;

    array = readArrayFromFile(path, &size);
    if (array != NULL) {
        printf("\nFile: %s | Array Lenght: %d items\n", path, size);
        benchAll(array, size);
        free(array);
        array = NULL;
    }
}

bool startsWith(const char *start, const char *str)
{
    return strncmp(start, str, strlen(start)) == 0;
}

int main(int argc, char* argv[]) {
    char path[256];
    char* file = NULL;

    if( argc > 1 ) {
        for(int i = 1; i < argc; i++) {
            if(strcmp("--help", argv[i]) == 0 || strcmp("-h", argv[i]) == 0) {
                printf("How to use:\n"
                       "./main                                  Runs the program testing all files included on number instances.\n"
                       "./main -f=example.txt -t=Bubble         Runs with custom arguments.\n"
                       "\n"
                       "Arguments:\n"
                       "--help, -h                              Display all the program commands and arguments.\n"
                       "--file, -f                              Pass file path. E.g.: --file='example.txt'\n"
                       "--type, -t                              Pass sort method. E.g.: --type=Bubble\n"
                       "Types: Selection, Bubble, Insertion, Merge, Quick");
            } else if(startsWith("-f=", argv[i]) || startsWith("--file=", argv[i])) {
                if (startsWith("-f=", argv[i])) {
                    file = &argv[i][3];
                } else {
                    file = &argv[i][7];
                }
            } else if(startsWith("-t=", argv[i]) || startsWith("--type=", argv[i])) {
                int size;
                char* type = NULL;

                if (startsWith("-f=", argv[i])) {
                    type = &argv[i][3];
                } else {
                    type = &argv[i][7];
                }

                double time_taken;

                if(file) {
                    int* array = readArrayFromFile(file, &size);

                    for(int i = 0; i < 5; i++) {
                        if(strcmp(sortNames[i], type) == 0) {
                            time_taken = benchSort(sortFuncs[i], array, size);
                            printf("%sSort: %f seconds\n", sortNames[i], time_taken);
                            break;
                        }
                    }
                    
                } else {
                    printf("Please specify a file in order to benchmark it!\n");
                }
            }

        }

    } else {
        benchFromFile("couting.txt");

        for(int i = 1000; i <= 100000; i *= 10) {
            for(int j = 1; j <= 4; j++) {
                sprintf(path, "instancias-num/num.%d.%d.in", i, j);
                benchFromFile(path);
            }
        }
    }

    return 0;
}