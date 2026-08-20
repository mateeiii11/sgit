#include "objects.h"
#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include <string.h>
#include <dirent.h>
#include <stdbool.h>

#define SPACE_TERMINATOR_COUNT 4
#define BLOB_OR_TREE_COUNT 4

void file_parser(nod *sgitFile, char *fileName)
{
    if(sgitFile->type == TREE) return;
    FILE *f = fopen(fileName, "rb");
    if(f == NULL)
    {
        printf("file not opened\n");
        return;
    }
    fseek(f, 0, SEEK_END);
    long int size = ftell(f);
    fseek(f, 0, SEEK_SET);
    sgitFile->data.content = malloc(size + 1);
    fread(sgitFile->data.content, 1, size, f);
    sgitFile->data.content[size] = '\0';
    fclose(f);
}

void hash_blob(nod *sgitFile)
{
    if(sgitFile->type == TREE) return;
    size_t size = strlen("blob ") + strlen(sgitFile->data.content) + 1;
    char *buffer = malloc(size);
    strcpy(buffer, "blob ");
    strcat(buffer, sgitFile->data.content);
    sgitFile->hash = hash_string(buffer);
    free(buffer);
}

void create_partial_string(nod *currentNode, char **buffer, size_t *totalSize)
{
    short hashCount = get_int_count(currentNode->hash);
    char *string = malloc(hashCount + 1);
    snprintf(string, hashCount + 1, "%u", currentNode->hash);
    size_t size = BLOB_OR_TREE_COUNT + strlen(string)  + strlen(currentNode->name) + SPACE_TERMINATOR_COUNT;
    bool firstTime = 0;
    if(*totalSize == 0)
        firstTime = 1;
    *totalSize += size;
    *buffer = realloc(*buffer, *totalSize);
    if(firstTime == 1)
    {
        (*buffer)[0] = '\0';
        firstTime = 0;
    }

    if(currentNode->type == BLOB)
    {
        strcat(*buffer, "blob ");
        strcat(*buffer, string);
        strcat(*buffer, " ");
        strcat(*buffer, currentNode->name);
        strcat(*buffer, " ");
    }
    else if(currentNode->type == TREE)
    {
        strcat(*buffer, "tree ");
        strcat(*buffer, string);
        strcat(*buffer, " ");
        strcat(*buffer, currentNode->name);
        strcat(*buffer, " ");
    }
    free(string);
}


uint32_t hash_subdirectory(nod *currentDirectory)
{
    char *buffer = NULL;
    size_t bufferSize = 0;
    for(nod *p = currentDirectory->data.entry; p != NULL; p = p->next)
        create_partial_string(p, &buffer, &bufferSize);
    if(buffer == NULL)
        buffer = strdup("");
    uint32_t rezultat = hash_string(buffer);
    free(buffer);
    return rezultat; 
}

void free_tree_structure(nod *p)
{
    if(p->type == TREE && p->data.entry != NULL) free_tree_structure(p->data.entry);
    if(p->next != NULL) free_tree_structure(p->next);

    if(p->name != NULL)
        free(p->name);
    if(p->type == BLOB && p->data.content != NULL)
        free(p->data.content);
    free(p);

}



