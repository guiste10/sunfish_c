#ifndef SUNFISH_C_MAP_H
#define SUNFISH_C_MAP_H

#ifndef MAP_H
#define MAP_H

#include <stddef.h>

#define MAP_CAPACITY 16

typedef struct {
    char* key;
    void* value;
} Map_entry;

typedef struct {
    Map_entry entries[MAP_CAPACITY];
    size_t count;
} Map;

Map* map_create();
void map_put(Map* m, const char* key, void* value);
void* map_get(Map* m, const char* key);
void map_delete(Map* m, const char* key);
void map_destroy(Map* m);

#endif /* MAP_H */

#endif //SUNFISH_C_MAP_H
