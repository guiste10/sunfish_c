
#include "utils.h"
int indexOf(const char* str, char target) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == target) {
            return i;  // Return the index if the character is found
        }
        i++;
    }
    return -1;  // Return -1 if the character is not found
}