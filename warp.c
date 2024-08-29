


#include "headers.h"



char previous_dir[PATH_LEN] = "";

void warp(const char *path, char* home_dir) {
    char resolved_path[PATH_LEN];

    

    // If the path starts with "~/" or "~/", replace it with the user's home directory
    if (path[0] == '~' && (path[1] == '/' || path[1] == '\0')) {
        if (home_dir == NULL) {
            fprintf(stderr, "Unable to determine home directory.\n");
            return;
        }
        snprintf(resolved_path, sizeof(resolved_path), "%s%s", home_dir, path + 1);
        
    }


    // If the path is ".", use the current directory
    else if (strcmp(path, ".") == 0) {
        if (getcwd(resolved_path, sizeof(resolved_path)) == NULL) {
            perror("Error getting current directory");
            return;
        }
    }
    // If the path is "..", use the parent directory
    else if (strcmp(path, "..") == 0) {
        if (getcwd(resolved_path, sizeof(resolved_path)) == NULL) {
            perror("Error getting current directory");
            return;
        }
        char *last_slash = strrchr(resolved_path, '/');
        if (last_slash != NULL) {
            *last_slash = '\0';
        }
    }
    // If the path is "-", go back to the previous directory
    else if (strcmp(path, "-") == 0) {
        if (previous_dir[0] == '\0') {
            fprintf(stderr, "No previous directory available.\n");
            return;
        }
        strcpy(resolved_path, previous_dir);
    }
    // Otherwise, use the provided path directly
    else {
        strncpy(resolved_path, path, sizeof(resolved_path));
    }

    // Update the previous directory
    strcpy(previous_dir, getcwd(NULL, 0));

    if (chdir(resolved_path) == 0) {
        printf("Warped to: %s\n", resolved_path);
    } else {
        perror("Error warping");
    }
}
