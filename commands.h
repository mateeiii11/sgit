#ifndef COMMANDS_H
#define COMMANDS_H

void init();
void commit_files(char *message);
void sgitLog(const char commitHash[11]);
void status();
void checkout(const char commitHash[11]);
#endif 
