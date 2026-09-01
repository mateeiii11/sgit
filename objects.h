#ifndef OBJECTS_H
#define OBJECTS_H

#include <stdint.h>
#include <stdlib.h>
#include <time.h>
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

typedef struct commit
{
  uint32_t hash;
  char time[26];
  char *message;

  struct commit *parent;
  struct nod *head_tree;
} commit;

void file_parser(nod *sgitBlob, char *fileName);
void hash_blob(nod *sgitFile);
uint32_t hash_subdirectory(nod *sgitTree);
void free_tree_structure(nod *p);
#endif
