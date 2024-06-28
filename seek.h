void printFileContents(const char *filePath);
void seek(const char *target, const char *query, int recursive, int Direct_only, int File_only,int Exec_check,int* printflag,int*file_count_ptr,int*direct_count_ptr,char*dir_file_path);
void process_flag_seek(int* Direct_only,int*File_only,int* Exec_check,char*check);
void seek_main(const char* target,const char*query,int isDirectory,int isFile,int isExec,char*homeDir);
