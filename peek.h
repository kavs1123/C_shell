int isHidden(const char *name);
int compare(const void *a, const void *b);
char *get_parent_directory(const char *path);
void listFiles(const char *path, int showHidden, int showDetails);
void processflag(int*showHidden,int*showDetails,char*flag);
void peek(int showHidden, int showDetails, char *path, char *homeDir); 