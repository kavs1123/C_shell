#ifndef HEADERS_H_
#define HEADERS_H_

#include"defines.h"


#include <stdio.h>

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <pwd.h>
#include <sys/wait.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/stat.h>
#include <grp.h>
#include <time.h>
#include <fcntl.h>
#include <termios.h>

#include <limits.h>

#include <sys/time.h>
#include <signal.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "utilities.h"



#include "peek.h"
#include "proclore.h"
#include "prompt.h"
#include "seek.h"
#include "warp.h"
#include "pastevents.h"

struct BackgroundProcess {
    int pid;
    char name[MAX_INPUT_LENGTH];
    int ended; // 0 for not ended, 1 for ended normally, -1 for ended abnormally
};

#include "sighandle.h"
#include "activity.h"
#include "fg_bg.h"

#include "iman.h"

#include "neonate.h"
#include "ping.h"

#include "sighandle.h"

typedef struct global{
    char pastevents[MAX_PAST_EVENTS][MAX_COMMAND_LENGTH];
    char* homeDir;
    int pastflag;
    struct BackgroundProcess bg_processes[MAX_BG_PROCESSES];
    char path_of_file[4096];
    char *args[MAX_ARG_COUNT];
    char input[4096];

    char* command_copy;

    char *commands[INPUT_SIZE];

    int fg_id;

    int state_of_shell; // 0 for taking input , 1 for executing




}global;

typedef global* global_ptr;





#include "others.h"

void execute_the_command(char* command_to_pass ,global_ptr my_global);
void execute_the_command_with_io(char* command_input,global_ptr myglobal);
void execute_command_with_pipes(char* command_input,global_ptr myglobal);

void pastevents_main(char* command_from_main,char*user_input,char pastevents[MAX_PAST_EVENTS][MAX_COMMAND_LENGTH],char* path_of_file,global_ptr myglobal);
void pastevents_execute(char*command_input,global_ptr myglobal);

void run_shell(global_ptr my_global);


extern char previous_dir[PATH_LEN];

extern global_ptr global_ptr_i_am_sharing;
















#include "prompt.h"
#endif