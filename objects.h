#ifndef OBJECTS_H
#define OBJECTS_H

#include <stdint.h>
#include <stdlib.h>
typedef enum OBJ_TYPE
{
    BLOB,
    TREE
} OBJ_TYPE;

typedef struct blob
{
    char *content;
    size_t size;
}blob;

typedef struct nod
{
    uint32_t hash;
    char *name;
    OBJ_TYPE type;
    union
    {
        struct blob *file;
        struct nod *entry;
    } data;

    struct nod *next;
} nod;

void file_parser(nod *sgitBlob, char *fileName);
void hash_blob(nod *sgitFile);
uint32_t hash_subdirectory(nod *sgitTree);
void free_tree_structure(nod *p);
#endif