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

void pastevents_execute(char*command_input,global_ptr myglobal){

    if(strchr(command_input,'|')!=NULL){
        execute_command_with_pipes(command_input,myglobal);
    }
    else if((strchr(command_input,'<')!=NULL)||(strchr(command_input,'>')!=NULL)){
        execute_the_command_with_io(command_input,myglobal);
    }
    else{
        execute_the_command(command_input,myglobal);
    }

    



    
    execute_the_command(command_input,myglobal);
    

 

        
}

void pastevents_main(char* command_from_main,char*user_input,char pastevents[MAX_PAST_EVENTS][MAX_COMMAND_LENGTH],char* path_of_file,global_ptr myglobal){
    
    
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

            if(isspace(pastevents[index - 1][strlen(pastevents[index - 1])-1])){
                pastevents[index - 1][strlen(pastevents[index - 1])-1]='\0';
            }


            
           
            pastevents_execute(pastevents[index - 1],myglobal);
            
           
        } 
        else {
            printf("Invalid index.\n");
        }
    }

}
