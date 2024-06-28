#include "headers.h"

char homeDir[1024];
char username[256];
char systemName[256];

void getSystemName(char *systemName, int maxSize) {
    if (gethostname(systemName, maxSize) == -1) {
        perror("gethostname");
        exit(EXIT_FAILURE);
    }
}

void getUsername(char *username, int maxSize) {
    struct passwd *pwd = getpwuid(getuid());
    if (pwd == NULL) {
        perror("getpwuid");
        exit(EXIT_FAILURE);
    }
    strncpy(username, pwd->pw_name, maxSize);
}

void getCurrentDirectory(char *currentDir, int maxSize) {
    if (getcwd(currentDir, maxSize) == NULL) {
        perror("getcwd");
        exit(EXIT_FAILURE);
    }
}

void makePathRelative(char *path, int maxSize,char*homeDir) {

    if (strncmp(path, homeDir, strlen(homeDir)) == 0) {
        // The path is within the program's directory
        memmove(path, "~", 1); // Replace the program's directory with ~
        memmove(path + 1, path + strlen(homeDir), strlen(path) - strlen(homeDir) + 1);
    }
}

void prompt_repeat() {


    char currentDir[1024];







    getCurrentDirectory(currentDir, sizeof(currentDir));
    makePathRelative(currentDir, sizeof(currentDir),homeDir);

    printf("<%s@%s:%s> ", username, systemName, currentDir);
    fflush(stdout);

        
}

void give_initial_prompt(){


    getUsername(username, sizeof(username));
    getSystemName(systemName, sizeof(systemName));
    getCurrentDirectory(homeDir, sizeof(homeDir));

   


}
