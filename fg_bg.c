#include "headers.h"
 
void fg(int pid){
    // Bring the process to the foreground
    if (kill(pid, SIGCONT) == -1) {
        perror("kill");
        printf("No such process found\n");
        return;
    }

    // Wait for the process to complete
    if (waitpid(pid, NULL, 0) == -1) {
        perror("waitpid");
        return;
    }

    // Bring the process to the foreground


} 

void bg(int pid){
    if (kill(pid, SIGCONT) == -1) {
        perror("kill");
        printf("No such process found\n");
        return;
    }

} 
    // Resume a stopped background process
