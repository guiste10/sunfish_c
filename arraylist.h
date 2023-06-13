#ifndef SUNFISH_C_ARRAYLIST_H
#define SUNFISH_C_ARRAYLIST_H

typedef struct {
    void** array;
    int size;
    int capacity;
} ArrayList;

ArrayList* createArrayList();
void arrayListAdd(ArrayList* list, void* element);
void* arrayListGet(ArrayList* list, int index);
void freeArrayList(ArrayList* list);

#endif //SUNFISH_C_ARRAYLIST_H
