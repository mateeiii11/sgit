#include "objects.h"
#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include <string.h>

void file_parser(blob *gitFile, char *fileName)
{
    FILE *f = fopen(fileName, "r");
    if(f == NULL)
        return;
    fseek(f, 0, SEEK_END);
    long int size = ftell(f);
    fseek(f, 0, SEEK_SET);
    gitFile->content = malloc(size + 1);
    fread(gitFile->content, 1, size, f);
    gitFile->content[size] = '\0';
    fclose(f);
}

void hash_blob(blob *gitFile)
{
    char *buffer = malloc(sizeof("blob ") + strlen(gitFile->content) + 1);
    strcpy(buffer, "blob ");
    strcat(buffer, gitFile->content);
    gitFile->hash = hash(buffer);
    free(buffer);
}