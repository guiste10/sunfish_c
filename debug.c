#include <stdio.h>

//
// Created by neiringu on 18-05-23.
//
void printIntArray(const int* arr, int size) {
    printf("Array:");
    for (int i = 0; i < size; i++) {
        if(i % 10 == 0){
            printf("\n");
        }
        printf("%d\t", arr[i]);
    }
    printf("\n");
}