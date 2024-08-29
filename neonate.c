#include "headers.h"


int is_number(const char *str) {
    // Check if a string is a number
    for (int i = 0; str[i]; i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

long get_latest_pid() {
    DIR *dp;
    struct dirent *entry;
    char *endptr;
    long max_pid = -1;  // Initialize with an invalid PID

    // Open the /proc directory
    dp = opendir("/proc");
    if (dp == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    // Iterate through the /proc directory
    while ((entry = readdir(dp))) {
        if (is_number(entry->d_name)) {
            long pid = strtol(entry->d_name, &endptr, 10);
            
            // Check if the conversion was successful and if this PID is higher than the previous max
            if (*endptr == '\0' && pid > max_pid) {
                max_pid = pid;
            }
        }
    }

    // Close the directory
    closedir(dp);

    return max_pid;
}

void die(const char *s) {
    perror(s);
    exit(1);
}

struct termios t1, t2;




void disableRawMode(int flags) {
    tcsetattr(STDIN_FILENO, TCSANOW, &t1);
    fcntl(STDIN_FILENO, F_SETFL, flags);
}

void enableRawMode(int flags) {
    tcgetattr(STDIN_FILENO, &t1);
    t2 = t1;
    t2.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &t2);
    setbuf(stdout, NULL);

    
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
}


void neomain(int time_arg){
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    enableRawMode(flags);
    char c;
    long int latest_pid = get_latest_pid();
    printf("%ld\n", latest_pid);

    
    time_t start_time, current_time;

    start_time = time(NULL);
    
    





    while (1) {
        latest_pid = get_latest_pid();


        current_time = time(NULL);

        if (current_time - start_time >= time_arg) {
            printf("%ld\n", latest_pid);
            start_time = current_time;
        }

        
        
        int pt = read(STDIN_FILENO,&c,1);

        if(pt>0){
            if(c=='x'){
                break;
            }
        }





        
    }
    disableRawMode(flags);
}



