#ifndef __PROMPT_H
#define __PROMPT_H

void getSystemName(char *systemName, int maxSize);
void getUsername(char *username, int maxSize);
void getCurrentDirectory(char *currentDir, int maxSize);

void makePathRelative(char *path, int maxSize,char*homeDir);
void prompt_repeat();
void give_initial_prompt();
#endif