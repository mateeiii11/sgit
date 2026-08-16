#ifndef OBJECTS_H
#define OBJECTS_H

#include <stdint.h>


typedef struct blob
{
    char *name;
    char *content;
    uint32_t hash;
    struct blob *nextBlob;
    struct tree *nextTree;
} blob;

typedef struct tree
{
   char *name;
   uint32_t hash;
   uint8_t depth;
   struct blob *nextBlob;
   struct tree *nextTree;
} tree;

void file_parser(blob *gitFile, char *fileName);
void hash_blob(blob *gitFile);
void hash_tree(tree *gitTree);
void init_tree(tree *sgitTree);
#endif