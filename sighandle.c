#include "headers.h"



void handle_ctrl_c(int sig){

    printf(" ctrl_c\n");

    
    
    if(global_ptr_i_am_sharing->state_of_shell==0){
        run_shell(global_ptr_i_am_sharing);
    }
    else{

        if (kill(global_ptr_i_am_sharing->fg_id, 0) == 0) {
        // Calculate the actual signal number by taking modulo 32

            kill(global_ptr_i_am_sharing->fg_id, SIGINT);

        } 
        
        run_shell(global_ptr_i_am_sharing);
    }

    



}

void handle_ctrl_z(int sig){

    printf(" ctrl-z\n");

    
    if(global_ptr_i_am_sharing->state_of_shell==0){
        run_shell(global_ptr_i_am_sharing);
    }
    else{

        if (kill(global_ptr_i_am_sharing->fg_id, 0) == 0) {
            // Calculate the actual signal number by taking modulo 32
            
            kill(global_ptr_i_am_sharing->fg_id, SIGSTOP);
            
        } 
        run_shell(global_ptr_i_am_sharing);
    }
    

    


}


    
    
