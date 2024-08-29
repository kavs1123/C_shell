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

int splitString(const char *input, const char *delimiter, char *tokens[], int max_tokens) {
    char *copy = strdup(input); // Create a copy of the input string
    if (copy == NULL) {
        return 0; // Memory allocation failed
    }

    char *token = strtok(copy, delimiter);
    int token_count = 0;

    while (token != NULL && token_count < max_tokens) {
        tokens[token_count] = strdup(token); // Allocate memory for each token
        if (tokens[token_count] == NULL) {
            // Memory allocation failed, clean up and return
            free(copy);
            for (int i = 0; i < token_count; i++) {
                free(tokens[i]);
            }
            return 0;
        }

        token = strtok(NULL, delimiter);
        token_count++;
    }

    free(copy); // Free the copy of the input string
    return token_count; // Return the number of tokens found
}