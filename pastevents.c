#include "headers.h"


int number_of_elements=0;

void add_to_pastevents(char pastevents[MAX_PAST_EVENTS][MAX_COMMAND_LENGTH], char *command) {
    
    if (strcmp(command, "pastevents") == 0 || strcmp(command, "pastevents purge") == 0) {
        return;
    }

    
    if (pastevents[0][0] != '\0' && strcmp(command, pastevents[0]) == 0) {
        return;
    }

    
    for (int i = MAX_PAST_EVENTS - 1; i > 0; i--) {
        strcpy(pastevents[i], pastevents[i - 1]);
    }

    
    strcpy(pastevents[0], command);
    number_of_elements++;
}



void load_pastevents(char pastevents[MAX_PAST_EVENTS][MAX_COMMAND_LENGTH],char*path_of_file) {
    FILE *file = fopen(path_of_file, "r");

    if (file != NULL) {
        for (int i = 1; i <= 2* MAX_PAST_EVENTS; i++) {


            char * ans = fgets(pastevents[i/2], MAX_COMMAND_LENGTH, file);

            if((i-1)%2!=0){
                continue;
            }
            else{
                number_of_elements++;
            }
            if (ans == NULL ) {
                pastevents[i/2][0] = '\0';
                number_of_elements--;
            }

        }
        fclose(file);
    }
}

void save_pastevents(char pastevents[MAX_PAST_EVENTS][MAX_COMMAND_LENGTH],char* path_of_file) {
    FILE *file = fopen(path_of_file, "w");
    if (file != NULL) {
        for (int i = 0; i < MAX_PAST_EVENTS; i++) {
            if (pastevents[i][0] != '\0') {
                fprintf(file, "%s\n", pastevents[i]);
            }
        }
        fclose(file);
    }
}

void pastevents_execute(char*command_input){
    char homeDir[1024];
    getCurrentDirectory(homeDir, sizeof(homeDir));

    struct BackgroundProcess bg_processes[MAX_BG_PROCESSES] = {0};
    int pastflag=0;
    

    char *command = strtok(command_input, " \t\n");
    char pastevents[MAX_PAST_EVENTS][MAX_COMMAND_LENGTH]={0};

    if (command == NULL) {
        printf("Invalid command.\n");
        return ;
    }

    char path_of_file[4096];
    sprintf(path_of_file,"%s/pastevents.txt",homeDir);

    load_pastevents(pastevents,path_of_file);

    char* command_copy = (char*)malloc(sizeof(char)*4096);
            
            
    strcpy(command_copy,command_input);

    

    

    // Handle "warp" command
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

void pastevents_main(char* command_from_main,char*user_input,char pastevents[MAX_PAST_EVENTS][MAX_COMMAND_LENGTH],char* path_of_file){
    
    
    if (command_from_main == NULL) {
        for (int i = number_of_elements; i >= 0; i--) {
            if (pastevents[i][0] != '\0') {
                printf("%s", pastevents[i]);
            }
        }
    } 
    else if (strcmp(command_from_main, "purge") == 0) {
        for (int i = 0; i < MAX_PAST_EVENTS; i++) {
            pastevents[i][0] = '\0';
        }
        number_of_elements=0;
        save_pastevents(pastevents,path_of_file);
        printf("Past events purged.\n");
    } 
    else if (strcmp(command_from_main, "execute") == 0) {

        int index = atoi(strtok(NULL, " \t\n"));
        
        if (index > 0 && index <= MAX_PAST_EVENTS && pastevents[index - 1][0] != '\0') {

            
           
            pastevents_execute(pastevents[index - 1]);
            
           
        } 
        else {
            printf("Invalid index.\n");
        }
    }

}
