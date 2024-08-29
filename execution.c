#include "headers.h"

void execute_the_command(char* command_to_pass ,global_ptr my_global){


    char *command = strtok(command_to_pass, " \t\n");

    if (command == NULL) {
        
        return ;
    }

    if (strcmp(command, "warp") == 0) {
        char *path = strtok(NULL, " \t\n");
        
        while (path != NULL) {
            warp(path, my_global->homeDir);
            path = strtok(NULL, " \t\n");
        }

        if(strstr(my_global->command_copy,"pastevents")==NULL){

            add_to_pastevents(my_global->pastevents, my_global->command_copy);
            save_pastevents(my_global->pastevents,my_global->path_of_file);
        }

    }
    else if (strcmp(command, "peek") == 0) {
        int showHidden=0;int showDetails=0;
        char*path=NULL;

        char* check = strtok(NULL," \t\n");
        
        if (check){

            while(check!=NULL && check[0]=='-' && check[1]!='\0'){
                

                processflag(&showHidden,&showDetails,check);
                
                check=strtok(NULL," \t\n");

            }
            
            path=check;
        }
        
        peek(showHidden,showDetails,path,my_global->homeDir);

        if(strstr(my_global->command_copy,"pastevents")==NULL){

            add_to_pastevents(my_global->pastevents, my_global->command_copy);
            save_pastevents(my_global->pastevents,my_global->path_of_file);
        }

        
    }
    else if(strcmp(command,"pastevents")==0){

        

        char* arg = strtok(NULL," \t\n");
        pastevents_main(arg,my_global->command_copy,my_global->pastevents,my_global->path_of_file,my_global);

    }
    else if(strcmp(command,"proclore")==0){
        char*arg = strtok(NULL," \t\n");

        proclore_main(arg);
        if(strstr(my_global->command_copy,"pastevents")==NULL){

            add_to_pastevents(my_global->pastevents, my_global->command_copy);
            save_pastevents(my_global->pastevents,my_global->path_of_file);
        }
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


        seek_main(target_dir,file_to_find,isDirectory,isFile,isexecute,my_global->homeDir);
        if(strstr(my_global->command_copy,"pastevents")==NULL){

            add_to_pastevents(my_global->pastevents, my_global->command_copy);
            save_pastevents(my_global->pastevents,my_global->path_of_file);
        }


        
            
        
    }
    else if(strcmp(command,"iMan")==0){
        char* command_to_fetch = strtok(NULL," \t\n");
        iman_main(command_to_fetch);
        if(strstr(my_global->command_copy,"pastevents")==NULL){

            add_to_pastevents(my_global->pastevents, my_global->command_copy);
            save_pastevents(my_global->pastevents,my_global->path_of_file);
        }

    }

    else if(strcmp(command,"ping")==0){
        char*parts = strtok(NULL," \t\n");
        if(parts ==NULL){
            printf("invalid format");
            return;
        }
        int pid = atoi(parts);
        parts = strtok(NULL," \t\n");
        if(parts == NULL){
            printf("invalid format");
            return;
        }
        int signal_num = atoi(parts);

        ping_main(pid,signal_num);
        if(strstr(my_global->command_copy,"pastevents")==NULL){

            add_to_pastevents(my_global->pastevents, my_global->command_copy);
            save_pastevents(my_global->pastevents,my_global->path_of_file);
        }
    }

    else if(strcmp(command,"neonate")==0){
        char*part1=NULL;char* part2=NULL;

        part1= strtok(NULL," \t\n");




        part2 = strtok(NULL," \t\n");

        if(part2!=NULL){

            int time_arg = atoi(part2);
            neomain(time_arg);
        }
        if(strstr(my_global->command_copy,"pastevents")==NULL){

            add_to_pastevents(my_global->pastevents, my_global->command_copy);
            save_pastevents(my_global->pastevents,my_global->path_of_file);
        }

    }

    else if(strcmp(command,"activities")==0){
        activity_main();
        if(strstr(my_global->command_copy,"pastevents")==NULL){

            add_to_pastevents(my_global->pastevents, my_global->command_copy);
            save_pastevents(my_global->pastevents,my_global->path_of_file);
        }
    }

    else if(strcmp(command,"fg")==0){
        char*pid_fg= strtok(NULL," \t\n");
        int pid = atoi(pid_fg);
        fg(pid);
        if(strstr(my_global->command_copy,"pastevents")==NULL){

            add_to_pastevents(my_global->pastevents, my_global->command_copy);
            save_pastevents(my_global->pastevents,my_global->path_of_file);
        }
    }
    
    else if(strcmp(command,"bg")==0){
        char*pid_bg= strtok(NULL," \t\n");
        int pid = atoi(pid_bg);
        bg(pid);
        if(strstr(my_global->command_copy,"pastevents")==NULL){

            add_to_pastevents(my_global->pastevents, my_global->command_copy);
            save_pastevents(my_global->pastevents,my_global->path_of_file);
        }
    }
    

    

    else {
        others_main(my_global->bg_processes,command);
        if(strstr(my_global->command_copy,"pastevents")==NULL){

            add_to_pastevents(my_global->pastevents, my_global->command_copy);
            save_pastevents(my_global->pastevents,my_global->path_of_file);
        }
    }
    

        
    
    my_global->pastflag=0;


}

    