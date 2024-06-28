#include "headers.h"


void printFileContents(const char *filePath) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        printf("File not found.\n");
        return;
    }

    char buffer[1024];  // You can adjust the buffer size according to your needs
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }
    printf("\n");

    fclose(file);
}

void remove_extension(char *filename) {
    char *dot = strrchr(filename, '.');
    if (dot && dot != filename) {
        *dot = '\0';
    }
}

void seek(const char *target, const char *query, int recursive, int Direct_only, int File_only,int Exec_check,int* printflag,int*file_count_ptr,int*direct_count_ptr,char*dir_file_path) {
    
    target = strdup(target);
    query = strdup(query);
    if(Direct_only==0&&File_only==0){
        Direct_only=1;
        File_only=1;
    }
    
    
    DIR *dir = opendir(target);
    if (dir == NULL) {
        
        return;
    }

    char check_for_files[MAX_PATH_LENGTH];

    strcpy(check_for_files,query);
    strcat(check_for_files,".");
    //printf("%s\n",check_for_files);

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if( (entry->d_name[0]== '.') || strstr(entry->d_name, "..") !=NULL) {
            continue;
        }

        // snprintf(full_path, MAX_PATH_LENGTH, "%s/%s", target, entry->d_name);

        // strcpy(str_to_send,full_path);





        if (File_only==1 && (entry->d_type == DT_REG) && (strstr(entry->d_name,check_for_files) != NULL)) {
            
            char full_path[MAX_PATH_LENGTH];
            snprintf(full_path, MAX_PATH_LENGTH, "%s/%s", target, entry->d_name);

            printf("\033[32m%s\033[0m\n", full_path);  // Green for files

            (*file_count_ptr)++;
            
            *printflag=1;

            strcpy(dir_file_path,full_path);
                
        }        
            
        if (Direct_only == 1 && (entry->d_type == DT_DIR) && (strcmp(entry->d_name, query) == 0)) {
            
            char full_path[MAX_PATH_LENGTH];
            snprintf(full_path, MAX_PATH_LENGTH, "%s/%s", target, entry->d_name);

            printf("\033[34m%s\033[0m\n", full_path);  // Blue for directories
            
            
            (*direct_count_ptr)++;
            
            
            *printflag=1;

            strcpy(dir_file_path,full_path);

        }

        

        if (recursive && (entry->d_type==DT_DIR)) {
            char full_path_dir[MAX_PATH_LENGTH];

            snprintf(full_path_dir, MAX_PATH_LENGTH, "%s/%s", target, entry->d_name);
            seek(strdup(full_path_dir), query, recursive, Direct_only, File_only,Exec_check,printflag,file_count_ptr,direct_count_ptr,dir_file_path);
        }

        

        

        //free(filename);
    }

    closedir(dir);

    

        

    
 
}



void process_flag_seek(int* Direct_only,int*File_only,int* Exec_check,char*check){
    if (strcmp(check,"-d")==0){
        *Direct_only=1;
    }
    else if(strcmp(check,"-f")==0){
        *File_only=1;
    }
    else if(strcmp(check,"-e")==0){
        *Exec_check=1;
    }
    else{
        printf("Wrong flag\n");
    }
}

void seek_main(const char* target,const char*query,int isDirectory,int isFile,int isExec,char*homeDir){
    int file_count=0;int direct_count=0;

    char dir_file_path[MAX_PATH_LENGTH];
    
    int printflag =0; 
    if(isDirectory==1 && isFile==1){
        printf("Wrong flags\n");
        return;
    }

    if(isDirectory==0 && isFile==0){
        isDirectory=1;
        isFile=1;
    }

    if(target==NULL){
        char string_cwd[MAX_PATH_LENGTH];
        snprintf(string_cwd, MAX_PATH_LENGTH, ".");
        target=string_cwd;
    }
    
    seek(target,query,1,isDirectory,isFile,isExec,&printflag,&file_count,&direct_count,dir_file_path);

    

    if(isExec){
        if(direct_count+file_count==1){
            if(direct_count==1){
                printf("%s\n",dir_file_path);
                warp(dir_file_path,homeDir);
                //printf("one direct\n");
            }
            else if(file_count==1){
                //printf("one file\n");
                printFileContents(dir_file_path);
                
                //print contents of the file
            }
        }
    }

    if(printflag ==0){
        printf("No matching files or directories found\n");
    }


}