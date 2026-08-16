#include "objects.h"
#include <stdio.h>
#include <stdlib.h>
#include "../hash/hash.h"
#include <string.h>
#include <dirent.h>
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

void get_dir_to_tree_struc(tree *gitTree)
{
        
}

void init_blob(blob *sgitBlob, char *fileName)
{
    file_parser(sgitBlob, "../content/test.txt");
    sgitBlob->nextBlob = NULL;
    sgitBlob->nextTree = NULL; 
    sgitBlob->name = "test.txt";
}
/** 
void init_tree(tree *sgitTree, char *dirName)
{
   sgitTree->name = malloc(strlen(dirName) + 1);
   sgitTree->name[strlen(dirName)] = '\0';
   sgitTree->nextTree = NULL;
   sgitTree->nextBlob = NULL;
}

*/
