#include "headers.h"

extern char previous_dir[PATH_LEN];




int isHidden(const char *name) {
    return (name[0] == '.');
}

int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

char *get_parent_directory(const char *path) {
    char *parent_path = NULL;

    if (path) {
        char *last_slash = strrchr(path, '/');
        if (last_slash) {
            // Calculate length of the parent path
            size_t parent_length = last_slash - path;
            if (parent_length == 0) {
                parent_length = 1; // Root directory case
            }

            parent_path = (char *)malloc(parent_length + 1);
            if (parent_path) {
                strncpy(parent_path, path, parent_length);
                parent_path[parent_length] = '\0';
            }
        }
    }

    return parent_path;
}



void listFiles(const char *path, int showHidden, int showDetails) {
    struct dirent *entry;
    int count =0;
    DIR *dir = opendir(path);

    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir)) != NULL) {
        if (!showHidden && isHidden(entry->d_name)) {
            continue;
            
        }
        count++;
    }
    char **filenames = (char **)malloc(count * sizeof(char *));
    if (filenames == NULL) {
        perror("malloc");
        closedir(dir);
        exit(EXIT_FAILURE);
    }

    // Populate filenames array
    rewinddir(dir);

    int index = 0;
    while ((entry = readdir(dir)) != NULL) {
        if (!showHidden && isHidden(entry->d_name)) {
            continue;
        }
        filenames[index] = strdup(entry->d_name);
        index++;
    }


    qsort(filenames, count, sizeof(char *), compare);

    for (int i = 0; i < count; i++){

        struct stat file_stat;
        char full_path[MAX_PATH_LENGTH];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, filenames[i]);

        if (stat(full_path, &file_stat) == -1) {
            perror("stat");
            closedir(dir);
            exit(EXIT_FAILURE);
        }


        if (showDetails) 
        {


            // File type and permissions
            printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
            printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
            printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
            printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
            printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
            printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
            printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
            printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
            printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
            printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");

            

            printf(" %2ld ", file_stat.st_nlink);  // Number of hard links
            printf("%-8s ", getpwuid(file_stat.st_uid)->pw_name);  // Owner
            printf("%-8s ", getgrgid(file_stat.st_gid)->gr_name);   // Group
            printf("%8ld ", file_stat.st_size);   // File size
            char time_buffer[80];
            strftime(time_buffer, sizeof(time_buffer), "%b %d %H:%M", localtime(&file_stat.st_mtime));
            printf("%s ", time_buffer);  // Last modification time

            if (S_ISDIR(file_stat.st_mode)) {
                printf(COLOR_DIRECTORY " %-8s\n " COLOR_DEFAULT, filenames[i]);
            } else if (file_stat.st_mode & S_IXUSR || file_stat.st_mode & S_IXGRP || file_stat.st_mode & S_IXOTH) {
                printf(COLOR_EXECUTABLE " %-8s\n " COLOR_DEFAULT, filenames[i]);
            } else {
                printf("%-8s\n ", filenames[i]);
            }


        }
        else
        {
            if (S_ISDIR(file_stat.st_mode)) {
                printf(COLOR_DIRECTORY " %-8s\n " COLOR_DEFAULT, filenames[i]);
            } 
            else if (file_stat.st_mode & S_IXUSR || file_stat.st_mode & S_IXGRP || file_stat.st_mode & S_IXOTH) {
                printf(COLOR_EXECUTABLE " %-8s\n " COLOR_DEFAULT, filenames[i]);
            } 
            else {
                printf("%-8s\n ", filenames[i]);
            }
        }
        free(filenames[i]);
    }
    free(filenames);

    closedir(dir);
}


void processflag(int*showHidden,int*showDetails,char*flag){
    if (strcmp(flag,"-la")==0||strcmp(flag,"-al")==0){
        *showHidden = 1;
        *showDetails = 1;
    }
    else if(strcmp(flag,"-a")==0){
        *showHidden = 1;

    }
    else if(strcmp(flag,"-l")==0){
        *showDetails=1;
    }
    else{
        printf("wrong flag");
        //exit();
    }

}





void peek(int showHidden, int showDetails, char *path, char *homeDir) {
    if (!path) {
        peek(showHidden, showDetails, getcwd(NULL, 0), homeDir);
        return;
    }

    // Handle special cases for path
    if (path[0] == '~' && (path[1] == '/' || path[1] == '\0')) {
        char *home_path = homeDir;
        if (home_path) {
            char full_path[MAX_PATH_LENGTH];
            snprintf(full_path, sizeof(full_path), "%s/%s", home_path, path + 2);
            peek(showHidden, showDetails, full_path, homeDir);
            return;
        } else {
            printf("Unable to determine home directory.\n");
            return;
        }
    } else if (strcmp(path, ".") == 0) {
        path = getcwd(NULL, 0);
    } else if (strcmp(path, "..") == 0) {
        char *parent_path = get_parent_directory(getcwd(NULL, 0)); // You need to implement get_parent_directory
        if (parent_path) {
            peek(showHidden, showDetails, parent_path, homeDir);
            //free(parent_path);
            return;
        } else {
            printf("Unable to determine parent directory.\n");
            return;
        }
    } else if (strcmp(path, "-") == 0) {
        char *prev_path = previous_dir; // You need to implement get_previous_directory
        if (prev_path) {
            peek(showHidden, showDetails, prev_path, homeDir);
            //free(prev_path);
            return;
        } else {
            printf("No previous directory available.\n");
            return;
        }
    } else if (path[0] == '.' && (path[1] == '/' || path[1] == '\0')) {
        char *current_path = getcwd(NULL, 0);
        if (current_path) {
            char full_path[MAX_PATH_LENGTH];
            snprintf(full_path, sizeof(full_path), "%s/%s", current_path, path + 2);
            peek(showHidden, showDetails, full_path, homeDir);
            free(current_path);
            return;
        } else {
            printf("Unable to determine current directory.\n");
            return;
        }
    }

    listFiles(path, showHidden, showDetails);
}
