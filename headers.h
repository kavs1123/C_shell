#ifndef HEADERS_H_
#define HEADERS_H_


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

#include <limits.h>

#include <sys/time.h>
#include <signal.h>

#include "utilities.h"

#include"defines.h"

#include "peek.h"
#include "proclore.h"
#include "prompt.h"
#include "seek.h"
#include "warp.h"
#include "pastevents.h"

struct BackgroundProcess {
    pid_t pid;
    char name[MAX_INPUT_LENGTH];
    int ended; // 0 for not ended, 1 for ended normally, -1 for ended abnormally
};
#include "others.h"

extern char previous_dir[PATH_LEN];
















#include "prompt.h"
#endif