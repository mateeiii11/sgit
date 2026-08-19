#include "sgit.h"
#include "hash.h"
#include "objects.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void hash_every_blob(nod *currentNode)
{
    if(currentNode->type == TREE && currentNode->data.entry != NULL)
        hash_every_blob(currentNode->data.entry);
    if(currentNode->next != NULL) 
        hash_every_blob(currentNode->next);
    if(currentNode->type == BLOB)
        hash_blob(currentNode);
}

void hash_every_tree()
{
    
}


void directory_concatenation(nod *p, nod *currDir)
{
    if(currDir->type == TREE && currDir->data.entry == NULL) 
        currDir->data.entry = p;
    else
    {
        nod *t;
        for(t = currDir->data.entry; t -> next != NULL; t = t->next)
            ;
        t -> next = p;
    }
    
}

void loop_through_directory(char *path, nod *currDir)
{
    DIR *directory = opendir(path);
    if(directory == NULL)
    {
        printf("Directory not opened\n");
        return;
    }
    struct dirent *de;
    while((de = readdir(directory)) != NULL)
    {
        if(strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0) continue;
        nod *p;
        p = malloc(sizeof(struct nod));
        if(de->d_type == DT_DIR)
        {
            p->type = TREE;
            p->name = strdup(de->d_name);
            p->data.entry = NULL;
            p->next = NULL;
            size_t bufferSize = strlen(path) + 1 + 
            strlen(de->d_name) + 1;
            char *buffer = malloc(bufferSize);
            strcpy(buffer, path);
            strcat(buffer, "/");
            strcat(buffer, de->d_name);
            loop_through_directory(buffer, p);
            directory_concatenation(p, currDir);
            free(buffer);
        }
        else  
        {
           p->type = BLOB;
           p->name = strdup(de->d_name);
           size_t bufferSize = strlen(path) + 1 + 
           strlen(de->d_name) + 1;
           char *buffer = malloc(bufferSize);
           strcpy(buffer, path);
           strcat(buffer, "/");
           strcat(buffer, de->d_name);
           file_parser(p, buffer);
           p->next = NULL;
           directory_concatenation(p, currDir);
           free(buffer);
        }
    }
    closedir(directory);
}

nod* sgit_init(char *path)
{

    nod *head;
    head = malloc(sizeof(struct nod));
    head->name = "sgit";
    head->type = TREE;
    head->next = NULL;
    head->data.entry = NULL;
    loop_through_directory(path, head);
    hash_every_blob(head);
    return head;
}