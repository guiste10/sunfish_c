#ifndef SUNFISH_C_MAP_H
#define SUNFISH_C_MAP_H

#ifndef MAP_H
#define MAP_H

#include <stddef.h>

#define MAP_CAPACITY 16

typedef struct {
    char* key;
    void* value;
} map_entry;

typedef struct {
    map_entry entries[MAP_CAPACITY];
    size_t count;
} map;

map* map_create();
void map_put(map* m, const char* key, void* value);
void* map_get(map* m, const char* key);
void map_delete(map* m, const char* key);
void map_destroy(map* m);

#endif /* MAP_H */

#endif //SUNFISH_C_MAP_H
