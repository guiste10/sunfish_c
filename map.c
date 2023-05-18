#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"

map* map_create() {
    map* m = malloc(sizeof(map));
    m->count = 0;
    return m;
}

map_entry* find_entry(map* m, const char* key) {
    for (size_t i = 0; i < m->count; i++) {
        if (strcmp(m->entries[i].key, key) == 0) {
            return &m->entries[i];
        }
    }
    return NULL;
}

void map_put(map* m, const char* key, void* value) {
    map_entry* entry = find_entry(m, key);
    if (entry != NULL) {
        entry->value = value;
        return;
    }

    if (m->count >= MAP_CAPACITY) {
        fprintf(stderr, "Map is full!\n");
        exit(1);
    }

    map_entry* new_entry = &m->entries[m->count++];
    new_entry->key = strdup(key);
    new_entry->value = value;
}

void* map_get(map* m, const char* key) {
    map_entry* entry = find_entry(m, key);
    if (entry == NULL) {
        return NULL;
    }
    return entry->value;
}

void map_delete(map* m, const char* key) {
    map_entry* entry = find_entry(m, key);
    if (entry == NULL) {
        return;
    }

    free(entry->key);
    entry->key = NULL;
    entry->value = NULL;

    // Move the last entry into the deleted entry's slot
    map_entry* last_entry = &m->entries[--m->count];
    entry->key = last_entry->key;
    entry->value = last_entry->value;
    last_entry->key = NULL;
    last_entry->value = NULL;
}

void map_destroy(map* m) {
    for (size_t i = 0; i < m->count; i++) {
        free(m->entries[i].key);
        m->entries[i].key = NULL;
        m->entries[i].value = NULL;
    }
    free(m);
}
