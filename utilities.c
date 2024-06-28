#include "headers.h"


void replaceStringInPlace(char *input, const char *old_str, const char *new_str) {
    const size_t old_len = strlen(old_str);
    const size_t new_len = strlen(new_str);

    char *ptr = input;
    while ((ptr = strstr(ptr, old_str)) != NULL) {
        if (old_len != new_len) {
            memmove(ptr + new_len, ptr + old_len, strlen(ptr + old_len) + 1);
        }
        memcpy(ptr, new_str, new_len);
        ptr += new_len;
    }
}