
#include "headers.h"

global_ptr global_ptr_i_am_sharing =NULL;




void run_shell(global_ptr my_global){

    const char* ampersand = "&";
    const char* ampersand_semi="&;";

    

    while (1) {

        sigset_t oldmask; sigemptyset(&oldmask); sigprocmask(SIG_BLOCK, NULL, &oldmask); 
        sigaddset(&oldmask, SIGTSTP);
        sigaddset(&oldmask, SIGINT);
        sigaddset(&oldmask, SIGQUIT);
        sigprocmask(SIG_UNBLOCK, &oldmask, NULL);

        check_bg_processes(my_global->bg_processes);

        prompt_repeat();

        my_global->state_of_shell=0;

        
        // printf("this is fine\n");
    
        char* checker = fgets(my_global->input, 4096, stdin);

        if(checker==NULL){
            printf("\n");
            
            exit(0);
        }

        


        replaceStringInPlace(my_global->input,ampersand,ampersand_semi);

          

        
        int commandCount = 0;
        my_global->state_of_shell=1;
        char *command = strtok(my_global->input, ";");
        while (command != NULL && commandCount < INPUT_SIZE) {

            my_global->commands[commandCount] = command;
            commandCount++;
            command = strtok(NULL, ";");
        }

        
        for (int i = 0; i < commandCount; i++) {

            
            my_global->command_copy = (char*)malloc(sizeof(char)*4096);
            
            
            strcpy(my_global->command_copy,my_global->commands[i]);



            if(strchr(my_global->commands[i],'|')!=NULL){
                execute_command_with_pipes(my_global->commands[i],my_global);
            }

            else if((strchr(my_global->commands[i],'<')!=NULL)||(strchr(my_global->commands[i],'>')!=NULL)){

                execute_the_command_with_io(my_global->commands[i],my_global);
            }
            else{
                execute_the_command(my_global->commands[i],my_global);
            }



            

        }
    }

}


int main() {
    

    
    global_ptr  my_global = (global_ptr)malloc(sizeof(global));

    my_global->homeDir=(char*)malloc(sizeof(char)*1024);


    memset(my_global->bg_processes,0,MAX_BG_PROCESSES*sizeof(struct BackgroundProcess));

    my_global->pastflag=0;



    global_ptr_i_am_sharing = my_global;

    // Keep accepting commands

    // char homeDir[1024];
    // int pastflag=0;
    // struct BackgroundProcess bg_processes[MAX_BG_PROCESSES] = {0};

    const char* ampersand = "&";
    const char* ampersand_semi="&;";

    for(int i=0; i<MAX_PAST_EVENTS;i++){
        memset(my_global->pastevents[i],0,MAX_COMMAND_LENGTH*sizeof(char));
    }



    getcwd(my_global->homeDir,1024*sizeof(char));








    // char path_of_file[4096];
    sprintf(my_global->path_of_file,"%s/pastevents.txt",my_global->homeDir);

    load_pastevents(my_global->pastevents,my_global->path_of_file);

    give_initial_prompt();

    signal(SIGINT, handle_ctrl_c);
    signal(SIGTSTP, handle_ctrl_z);

    run_shell(my_global);


    

    return 0;
}

