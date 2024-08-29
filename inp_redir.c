#include "headers.h"

void execute_the_command_with_io(char* command_input,global_ptr myglobal){


    // printf("reached here \n");
    int has_inp=0;
    int has_ouput=0;
    int is_append=0;
    char* output_file=NULL;
    char* input_file =NULL;
    char*command_to_give_func=NULL;
    

    
    for(int i=0;i<strlen(command_input);i++){
        if(command_input[i]=='<'){
            has_inp=1;
        }
        if(command_input[i]=='>'){
            has_ouput=1;
        }
        
    }

    if(strstr(command_input,">>")!=NULL){
        is_append=1;

    }

    char* duplicate1 = strdup(command_input);
    if(has_inp==0){
        if(has_ouput){
            if(is_append){

                char* token = strtok(duplicate1,">>");
                command_to_give_func = token;

                token = strtok(NULL,">>");
                output_file=token;
                
                
            }
            else{
                char* token = strtok(duplicate1,">");
                command_to_give_func = token;

                token = strtok(NULL,">");
                output_file=token;

            }
        

        }


    }
    else{
        if(has_ouput){
            if(is_append){
                char* token = strtok(duplicate1,">>");
                char* intermediate = token;

                token = strtok(NULL,">>");
                output_file=token;

                char* check = strtok(intermediate,"<");
                command_to_give_func = check;
                check = strtok(NULL,"<");
                input_file = check;

            }
            else{
                char* token = strtok(duplicate1,">");
                char* intermediate = token;

                token = strtok(NULL,">");
                output_file=token;

                char* check = strtok(intermediate,"<");
                command_to_give_func = check;
                check = strtok(NULL,"<");
                input_file = check;

            }
        }
        else{
            char* token = strtok(duplicate1,"<");
            command_to_give_func = token;
            token = strtok(NULL,"<");
            input_file = token;


        }

    }


    
    if(isspace(command_to_give_func[strlen(command_to_give_func)-1])){
        command_to_give_func[strlen(command_to_give_func)-1]='\0';
    }
    if(isspace(command_to_give_func[0])){
        command_to_give_func++;
    }
    if(input_file){

        if(isspace(input_file[strlen(input_file)-1])){
            input_file[strlen(input_file)-1]='\0';
        }
        if(isspace(input_file[0])){
            input_file++;
        }
    }

    if(output_file){

        if(isspace(output_file[strlen(output_file)-1])){
            output_file[strlen(output_file)-1]='\0';
        }
        if(isspace(output_file[0])){
            output_file++;
        }
    }


    // printf("%s %s %s %d %d %d\n",command_to_give_func,input_file,output_file,has_inp,has_ouput,is_append);

    if(has_inp==0){
        int original_stdout = dup(STDOUT_FILENO);
        
        if(is_append){
            
            int fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1) {
                perror("Open failed");
                exit(1);
            }
            
            // Duplicate the file descriptor to STDOUT
            if (dup2(fd, STDOUT_FILENO) == -1) {
                perror("Duplication failed");
                exit(1);
            }
            
            close(fd);

            // Execute the command
            execute_the_command(command_to_give_func,myglobal);
            dup2(original_stdout, STDOUT_FILENO);
            close(original_stdout);
        }
        else{
            int fd = open(output_file, O_WRONLY | O_CREAT , 0644);
            if (fd == -1) {
                perror("Open failed");
                exit(1);
            }
            
            // Duplicate the file descriptor to STDOUT
            if (dup2(fd, STDOUT_FILENO) == -1) {
                perror("Duplication failed");
                exit(1);
            }
            
            close(fd);



            // Execute the command
            execute_the_command(command_to_give_func,myglobal);

            dup2(original_stdout, STDOUT_FILENO);
            close(original_stdout);

        }
    }

    else{

        // FILE* file;

        // char *args[MAX_ARGS];
        // args[0]=command_to_give_func;

        int original_stdout = dup(STDOUT_FILENO);

        int original_stdin = dup(STDIN_FILENO);

        int fd_inp = open(input_file, O_RDONLY);

        // file = fopen(input_file, "r");

        if (dup2(fd_inp, STDIN_FILENO) == -1) {
            perror("Duplication failed");
            exit(1);
        }
        
        close(fd_inp);



       





        if(has_ouput){

            if(is_append){
                
                int fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
                if (fd == -1) {
                    perror("Open failed");
                    exit(1);
                }
                
                // Duplicate the file descriptor to STDOUT
                if (dup2(fd, STDOUT_FILENO) == -1) {
                    perror("Duplication failed");
                    exit(1);
                }
                
                close(fd);

                // Execute the command
                execute_the_command(command_to_give_func,myglobal);
                dup2(original_stdout, STDOUT_FILENO);
                close(original_stdout);
            }
            else{
                int fd = open(output_file, O_WRONLY | O_CREAT , 0644);
                if (fd == -1) {
                    perror("Open failed");
                    exit(1);
                }
                
                // Duplicate the file descriptor to STDOUT
                if (dup2(fd, STDOUT_FILENO) == -1) {
                    perror("Duplication failed");
                    exit(1);
                }
                
                close(fd);



                // Execute the command
                execute_the_command(command_to_give_func,myglobal);

                dup2(original_stdout, STDOUT_FILENO);
                close(original_stdout);

            }
        }

        else{

            execute_the_command(command_to_give_func,myglobal);

        }

        dup2(original_stdin, STDIN_FILENO);
        close(original_stdin);

        

    
    }








}




    


