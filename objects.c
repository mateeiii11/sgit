#include "objects.h"
#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include <string.h>
#include <dirent.h>
void file_parser(nod *sgitFile, char *fileName)
{
    FILE *f = fopen(fileName, "r");
    if(f == NULL)
    {
        printf("file not opened\n");
        return;
    }
    fseek(f, 0, SEEK_END);
    long int size = ftell(f);
    fseek(f, 0, SEEK_SET);
    (sgitFile)->data.content = malloc(size + 1);
    fread((sgitFile)->data.content, 1, size, f);
    (sgitFile)->data.content[size] = '\0';
    fclose(f);
}

void hash_blob(nod *sgitFile)
{
    printf("Nume: %s\n", sgitFile->name);
    printf("Content e NULL? %s\n", sgitFile->data.content == NULL ? "DA" : "NU");
    if(sgitFile->data.content == NULL) return;
    size_t size = sizeof("blob ") + strlen(sgitFile->data.content) + 1;
    char *buffer = malloc(size);
    strcpy(buffer, "blob ");
    strcat(buffer, sgitFile->data.content);
    sgitFile->hash = hash(buffer);
    free(buffer);
}


void view(nod *p)
{
    printf("%s\n", p->name);
    if(p->type == TREE && p->data.entry != NULL) view(p->data.entry);
    if(p->next != NULL) view(p->next);
}


