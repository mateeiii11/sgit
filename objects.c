#include "objects.h"
#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include <string.h>
#include <dirent.h>
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
    sgitFile->hash = hash(buffer);
    free(buffer);
}



