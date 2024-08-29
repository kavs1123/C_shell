#include "headers.h"


void exec_ping(int process,int signal_num){
    
    
    
        // Check if the process with the given PID exists
    if (kill(process, 0) == 0) {
        // Calculate the actual signal number by taking modulo 32
        signal_num = signal_num % 32;
        kill(process, signal_num);
        printf("Sent signal %d to process %d\n", signal_num, process);
    } 
    else {
        printf("No such process found with PID %d\n", process);
    }
    
    
}

void ping_main(int process , int signal_num){
    exec_ping(process,signal_num);

}