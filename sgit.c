#include "sgit.h"
#include "objects.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void dir_cat(nod *p, nod *currDir)
{
   if(currDir->data.entry == NULL) 
        currDir->data.entry = p;
   else
   {
       nod *t;
       for(t = currDir->data.entry; t -> next != NULL; t = t->next);
       t -> next = p;
   }
    
}

void loop_through_dir(char *path, nod *currDir)
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
        if(strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0 
    || strcmp(de->d_name, ".git") == 0) continue;
        nod *p;
        p = malloc(sizeof(struct nod));
        if(de->d_type ==DT_REG) 
        { 
           p->type = BLOB;
           p->name = strdup(de->d_name);
           size_t bufferSize = strlen(path) + 1 + 
           strlen(de->d_name) + 1;
           char *buffer = malloc(bufferSize);
           strcpy(buffer, path);
           strcat(buffer, "/");
           strcat(buffer, de->d_name);
           buffer[bufferSize - 1] = '\0';
           file_parser(p, buffer);
           ///printf("%s\n", buffer);
           p->data.entry = NULL;
           p->next = NULL;
           dir_cat(p, currDir);
           free(buffer);
        }
        else if(de->d_type == DT_DIR)
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
            buffer[bufferSize - 1] = '\0';
            ///printf("%s\n", buffer);
            loop_through_dir(buffer, p);
            dir_cat(p, currDir);
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
    loop_through_dir(path, head);
    
    return head;
}