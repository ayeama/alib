#include <stdlib.h>
#include <string.h>

char* a_strdup(const char* s) {
    char* d = malloc(strlen(s) + 1);
    if (d == NULL) {
        return NULL;
    }
    strcpy(d, s);
    return d;
}
