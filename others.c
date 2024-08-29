#include "headers.h"




void execute_command(char *args[], int background, struct BackgroundProcess bg_processes[]) {
    pid_t pid = fork();

    if (pid == 0) {  // Child process
        execvp(args[0], args);
        printf("'%s' is not a valid command \n",args[0]);
        exit(1);
    } else if (pid > 0) {  // Parent process
        global_ptr_i_am_sharing->fg_id=pid;
        if (!background) {
            struct timeval start, end;
            gettimeofday(&start, NULL);
            
            int status;
            waitpid(pid, &status, 0);
            
            gettimeofday(&end, NULL);
            double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
            
            if (elapsed > 2.0) {
                printf("Foreground process %s took %d seconds.\n", args[0], (int)elapsed);
            }
        } else {
            // Find an available slot for the background process
            int i;
            for (i = 0; i < MAX_BG_PROCESSES; i++) {
                if (bg_processes[i].pid == 0) {
                    bg_processes[i].pid = pid;
                    strcpy(bg_processes[i].name, args[0]);
                    bg_processes[i].ended = 0;
                    break;
                }
            }
            if (i == MAX_BG_PROCESSES) {
                printf("Maximum number of background processes reached.\n");
            } else {
                printf("Background process started with PID: %d\n", pid);
            }
        }
    } else {
        perror("Fork error");
    }
}

void check_bg_processes(struct BackgroundProcess bg_processes[]) {
    for (int i = 0; i < MAX_BG_PROCESSES; i++) {
        if (bg_processes[i].pid != 0 && !bg_processes[i].ended) {
            int status;
            pid_t result = waitpid(bg_processes[i].pid, &status, WNOHANG);
            if (result > 0) {
                if (WIFEXITED(status)) {
                    printf("\nBackground process %s (PID: %d) ended normally.\n", bg_processes[i].name, bg_processes[i].pid);
                    bg_processes[i].ended = 1;
                } else if (WIFSIGNALED(status)) {
                    printf("\nBackground process %s (PID: %d) ended abnormally.\n", bg_processes[i].name, bg_processes[i].pid);
                    bg_processes[i].ended = -1;
                }
            }
        }
    }
}

void others_main(struct BackgroundProcess bg_processes[],char*command){
    char input[MAX_INPUT_LENGTH];
    char *args[MAX_ARGS];
    
    
    char *token = strtok(NULL, " \t\n");
    int arg_count = 1;

    args[0]=command;



    while (token != NULL) {
        args[arg_count++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[arg_count] = NULL;


    

    
    int background = 0;
    if (strcmp(args[arg_count - 1], "&") == 0) {
        background = 1;
        args[arg_count - 1] = NULL;
    }
    
    if (strcmp(args[0], "exit") == 0) {
        exit(1);
    }
    
    execute_command(args, background, bg_processes);
    

}