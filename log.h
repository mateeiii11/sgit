#ifndef LOG_H
#define LOG_H

void parse_hash(char *buffer, char *childHash, int space);
void get_root_from_commit(const char commitHash[11], char *childHash, int space);

#endif

