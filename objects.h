#ifndef OBJECTS_H
#define OBJECTS_H

#include <stdint.h>
typedef enum OBJ_TYPE
{
    BLOB,
    TREE
} OBJ_TYPE;
typedef struct nod
{
    uint32_t hash;
    char *name;
    OBJ_TYPE type;
    union
    {
        char *content;
        struct nod *entry;
    } data;

    struct nod *next;
} nod;

void file_parser(nod *sgitBlob, char *fileName);
void hash_blob(nod *sgitFile);
uint32_t hash_subdirectory(nod *sgitTree);
#endif