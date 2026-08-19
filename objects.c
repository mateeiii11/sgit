#include "objects.h"
#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include <string.h>
#include <dirent.h>
#include <stdbool.h>

#define SPACE_TERMINATOR_SIZE 4

void file_parser(nod *sgitFile, char *fileName)
{
    if(sgitFile->type == TREE) return;
    FILE *f = fopen(fileName, "r");
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
    size_t size = sizeof("blob ") + strlen(sgitFile->data.content) + 1;
    char *buffer = malloc(size);
    strcpy(buffer, "blob ");
    strcat(buffer, sgitFile->data.content);
    sgitFile->hash = hash_string(buffer);
    free(buffer);
}

void create_partial_string(nod *currentNode, char **buffer, size_t *totalSize)
{
    char *string = hash_intToString(currentNode->hash);
    size_t size = sizeof("blob") + strlen(string)  + strlen(currentNode->name) + SPACE_TERMINATOR_SIZE;
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
    uint32_t rezultat = hash_string(buffer);
    free(buffer);
    return rezultat; 
}



