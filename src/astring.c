#include <stdlib.h>
#include <string.h>

char* a_strdup(const char* s) {
    char* d = malloc(sizeof(char) * (strlen(s) + 1));
    if (d == NULL) {
        return NULL;
    }
    return strcpy(d, s);
}

char* a_strndup(const char* s, size_t n) {
    char* d = malloc(sizeof(char) * (n + 1));
    if (d == NULL) {
        return NULL;
    }
    return strncpy(d, s, n);
}
