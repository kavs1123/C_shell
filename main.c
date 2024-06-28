
#include "headers.h"

int main() {
    // Keep accepting commands
    char *args[MAX_ARG_COUNT];
    char input[4096];
    char homeDir[1024];
    int pastflag=0;
    struct BackgroundProcess bg_processes[MAX_BG_PROCESSES] = {0};

    const char* ampersand = "&";
    const char* ampersand_semi="&;";

    char pastevents[MAX_PAST_EVENTS][MAX_COMMAND_LENGTH]={0};
    getCurrentDirectory(homeDir, sizeof(homeDir));

    char path_of_file[4096];
    sprintf(path_of_file,"%s/pastevents.txt",homeDir);

    load_pastevents(pastevents,path_of_file);

    give_initial_prompt();
    while (1) {

        check_bg_processes(bg_processes);

        prompt_repeat();
    
        fgets(input, 4096, stdin);

        replaceStringInPlace(input,ampersand,ampersand_semi);

        char *commands[INPUT_SIZE];  

        
        int commandCount = 0;
        char *command = strtok(input, ";");
        while (command != NULL && commandCount < INPUT_SIZE) {

            commands[commandCount] = command;
            commandCount++;
            command = strtok(NULL, ";");
        }

        
        for (int i = 0; i < commandCount; i++) {

            
            char* command_copy = (char*)malloc(sizeof(char)*4096);
            
            
            strcpy(command_copy,commands[i]);

            char *command = strtok(commands[i], " \t\n");

            if (command == NULL) {
                printf("Invalid command.\n");
                return 1;
            }

            if (strcmp(command, "warp") == 0) {
                char *path = strtok(NULL, " \t\n");
                while (path != NULL) {
                    warp(path, homeDir);
                    path = strtok(NULL, " \t\n");
                }

                add_to_pastevents(pastevents, command_copy);
                save_pastevents(pastevents,path_of_file);
            }
            else if (strcmp(command, "peek") == 0) {
                int showHidden=0;int showDetails=0;
                char*path;

                char* check = strtok(NULL," \t\n");
                
                if (check){

                    while(check!=NULL && check[0]=='-' && check[1]!='\0'){
                        

                        processflag(&showHidden,&showDetails,check);
                        
                        check=strtok(NULL," \t\n");

                    }
                    
                    path=check;
                }
                
                peek(showHidden,showDetails,path,homeDir);

                add_to_pastevents(pastevents, command_copy);
                save_pastevents(pastevents,path_of_file);

                
            }
            else if(strcmp(command,"pastevents")==0){

                

                char* arg = strtok(NULL," \t\n");
                pastevents_main(arg,command_copy,pastevents,path_of_file);

            }
            else if(strcmp(command,"proclore")==0){
                char*arg = strtok(NULL," \t\n");

                proclore_main(arg);
                add_to_pastevents(pastevents, command_copy);
                save_pastevents(pastevents,path_of_file);
            }

            else if(strcmp(command,"seek")==0){
                int isDirectory=0;int isFile=0;int isexecute =0;
                char* target_dir;
                char* file_to_find;
                char*check =strtok(NULL," \t\n");
                while(check[0]=='-'){
                    process_flag_seek(&isDirectory,&isFile,&isexecute,check);
                    
                    check=strtok(NULL," \t\n");
                }
                file_to_find=check;

                target_dir=strtok(NULL," \t\n");


                seek_main(target_dir,file_to_find,isDirectory,isFile,isexecute,homeDir);

                add_to_pastevents(pastevents, command_copy);
                save_pastevents(pastevents,path_of_file);


                
                    
                
            }
            else {
                others_main(bg_processes,command);
                add_to_pastevents(pastevents, command_copy);
                save_pastevents(pastevents,path_of_file);
            }
            

                
            
            free(command_copy);
            pastflag=0;

        }
    }

    return 0;
}

