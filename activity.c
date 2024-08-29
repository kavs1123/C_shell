#include "headers.h"

void listProcesses(int shellPid) {
    DIR *dir;
    struct dirent *entry;
    char path[4096];
    char line[256];

    

    // Open the /proc directory
    dir = opendir("/proc");
    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    // Print the header
    printf("%-10s %-10s %s\n", "PID", "State", "Command");

    // Iterate over processes in /proc
    while ((entry = readdir(dir)) != NULL) {
        if (isdigit(entry->d_name[0])) {
            // Build the path to the status file for this process
            sprintf(path, "/proc/%s/status", entry->d_name);

            // Open the status file
            FILE *fp = fopen(path, "r");
            if (fp == NULL) {
                continue; // Skip if we can't open the file
            }

            int pid = atoi(entry->d_name);
            int PPid = -1;
            char state[256];
            char cmd[256];

            // Read lines from the status file
            while (fgets(line, sizeof(line), fp) != NULL) {

                
                if (sscanf(line, "PPid: %d", &PPid) == 1) {

                    // Read the parent process ID
                }
                if (sscanf(line, "State: %s", state) == 1) {
                    // Read the process state
                }
                if (sscanf(line, "Name: %s", cmd) == 1) {
                    // Read the command name
                }
                // printf(" %d %d %s %s\n", shellPid,ppid,state,cmd);
            }


            // Check if this process is running and has the same parent ID as the shell
            if (PPid == shellPid && (strcmp(state, "S") == 0)) {
                printf("%-10d %-10s %s\n", pid, "running", cmd);
            }

            fclose(fp);
        }
    }

    closedir(dir);
}

void activity_main() {
    int shellpid = getpid(); // Get the GID of the shell (assuming this program is run from the shell)
    listProcesses(shellpid);
    return;
}
