#ifndef OBJECTS_H
#define OBJECTS_H

#include <stdint.h>

typedef struct blob
{
    char *content;
    uint32_t hash;
} blob;



void file_parser(blob *gitFile, char *fileName);
void hash_blob(blob *gitFile);
#endif