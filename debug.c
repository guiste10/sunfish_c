#include <stdio.h>
#include <malloc.h>
#include "move.h"

//
// Created by neiringu on 18-05-23.
//
void printIntArray(const int* arr, int size) {
    printf("Array:");
    for (int i = 0; i < size; i++) {
        if(i % 10 == 0){
            printf("\n");
        }
        printf("%d\t", arr[i]); // similar to  *(arr + i)
        fflush(stdout);  // Flush the output stream
    }
    printf("\n");
    fflush(stdout);  // Flush the output stream
}

void printCharArray(const char* arr, int size) {
    printf("Array:");
    for (int i = 0; i < size; i++) {
        if (i % 10 == 0) {
            printf("\n");
            fflush(stdout);  // Flush the output stream
        }
        printf("%c\t", arr[i]);
        fflush(stdout);  // Flush the output stream
    }
    printf("\n");
    fflush(stdout);  // Flush the output stream
}

void printMove(const Move move, const char board[]) {
    //printf("Move: %c from i = %d to j = %d, prom = %c\n", board[move.i], move.i, move.j, move.prom);
    char* from = render(move.i);
    char* to = render(move.j);
    printf("Move %c from i = %s to j = %s, prom = %c\n", board[move.i], from, to, move.prom);
    free(from);
    free(to);
    fflush(stdout);  // Flush the output stream
}