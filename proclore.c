#include "headers.h"

char getProcessStatus(pid_t pid) {
    char status = 'U'; // Default status: Unknown

    // Generate the path to the process status file
    char statusFilePath[50];
    snprintf(statusFilePath, sizeof(statusFilePath), "/proc/%d/status", pid);

    FILE *statusFile = fopen(statusFilePath, "r");
    if (statusFile == NULL) {
        perror("Error opening status file");
        exit(EXIT_FAILURE);
    }

    char line[128];
    while (fgets(line, sizeof(line), statusFile)) {
        if (strncmp(line, "State:", 6) == 0) {
            char state;
            if (sscanf(line, "State:\t%c", &state) == 1) {
                status = state;
                break;
            }
        }
    }

    fclose(statusFile);
    return status;
}


void printProcessInfo(pid_t pid) {
    // Print PID
    printf("PID: %d\n", pid);

    // Determine process status
    char status = getProcessStatus(pid);

    // Print Process Status
    printf("Process Status: %c%c\n", status, (pid != getpid()) ? '+' : ' ');

    // Print Process Group (same as PID for this example)
    printf("Process Group: %d\n", pid);

    // Print Virtual Memory (Placeholder value)
    printf("Virtual Memory: %d KB\n", pid * 1024);

    // Determine executable path using /proc/pid/exe symlink
    char exePath[512];
    snprintf(exePath, sizeof(exePath), "/proc/%d/exe", pid);
    char resolvedPath[MAX_PATH_LENGTH];
    ssize_t len = readlink(exePath, resolvedPath, sizeof(resolvedPath) - 1);
    if (len != -1) {
        resolvedPath[len] = '\0';
        printf("Executable Path: %s\n", resolvedPath);
    } else {
        printf("Executable Path: Unknown\n");
    }
}

void proclore_main(char* argument){
    //char input[100];
    pid_t my_pid = getpid();

    

        // Remove newline character from input


    if (argument==NULL) {
        // Print information about the shell process itself
        printProcessInfo(my_pid);
    } 
    else{
        pid_t target_pid = atoi(argument);
        if (target_pid <= 0) {
            printf("Invalid PID!\n");
            
        }
        else{

            printProcessInfo(target_pid);
        }
        
        
    }
        
        

}

    
    
    
