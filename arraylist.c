//
// Created by neiringu on 28-05-23.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void** array;
    int size;
    int capacity;
} ArrayList;

ArrayList* createArrayList() {
    ArrayList* list = malloc(sizeof(ArrayList));
    list->array = malloc(sizeof(void*) * 10);  // initial capacity of 10
    list->size = 0;
    list->capacity = 10;
    return list;
}

void arrayListAdd(ArrayList* list, void* element) {
    if (list->size == list->capacity) {
        // Resize the array if capacity is reached
        list->capacity *= 2;
        void** temp = realloc(list->array, sizeof(void*) * list->capacity * 2);
        if (temp == NULL) {
            // Handle reallocation failure (e.g., error handling, freeing resources)
            // Here, we simply print an error message and return
            printf("Error: Failed to reallocate memory.\n");
            return;
        }
        list->array = temp;
        list->capacity *= 2;    }
    list->array[list->size++] = element;
}

void* arrayListGet(ArrayList* list, int index) {
    if (index >= 0 && index < list->size) {
        return list->array[index];
    }
    return NULL;
}

void freeArrayList(ArrayList* list) {
    free(list->array);
    free(list);
}