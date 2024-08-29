#include "headers.h"

void execute_command_with_pipes(char* command_input,global_ptr myglobal){
    int pipe_counter =0;
    int pipe_index=0;

    int fork_id;int inp_fd;

    for(int i=0;i<strlen(command_input);i++){
        if(command_input[i]=='|'){
            pipe_counter++;
        }
    }

    char* pipe_args[pipe_counter+1];

    

    char* token = strtok(command_input,"|");
    while(token!=NULL){
        pipe_args[pipe_index]=token;
        pipe_index++;
        token = strtok(NULL,"|");
    }

    for(int i=0;i<pipe_index;i++){
        int len_part = strlen(pipe_args[i]);
        if(isspace(pipe_args[i][len_part-1])){
            pipe_args[i][len_part-1]='\0';
        }
        if(isspace(pipe_args[i][0])){
            pipe_args[i]++;
        }
    }
     



    int** pipes = (int**)malloc(sizeof(int*)*(pipe_counter));
    for(int i=0;i<pipe_counter;i++){
        pipes[i]=(int*)malloc(sizeof(int)*2);
    }

    for(int i=0;i<pipe_counter;i++){
        if(pipe(pipes[i])==-1){
            perror("Pipe");
            printf("couldnt pipe");
            exit(1);
        }
    }

    inp_fd=STDIN_FILENO;


    for(int i=0;i< pipe_counter+1;i++){
        fork_id=fork();

        if(fork_id==-1){
            
            printf("failed fork\n");
            exit(1);
        }
        else if(fork_id==0){
            for(int j=0;j<pipe_counter;j++){
                for(int k=0;k<2;k++){
                    if((j==i && k==1)||(j==(i-1)&&k==0)){
  
                        continue;
                    }
                    close(pipes[j][k]);
                }
            }

            if(i>0){
                
                dup2(pipes[i-1][0],0);
            }
            if(i<pipe_counter){
                
                
                dup2(pipes[i][1],1);
            }
            
            // printf("%s\n",pipe_args[i]);

            if((strchr(pipe_args[i],'<')!=NULL )||(strchr(pipe_args[i],'>')!=NULL)){

                
                execute_the_command_with_io(pipe_args[i],myglobal);
            }
            else{

                execute_the_command(pipe_args[i],myglobal);
            }



            exit(1);

        }
    }
    for(int i=0;i<pipe_counter;i++){
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    for(int i=0;i < pipe_counter+1;i++){
        wait(NULL);
    }

    
    
}