#include "sgit.h"
#include "objects.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

nod *head;

void get_last_node(nod *p)
{
    if(p->type == BLOB)
    {
        if(head->data.entry == NULL)
            head->data.entry = p;
        else
        {
            nod *t;
            for(t = head->data.entry; t -> next!= NULL; t = t->next);
            t->next = p;
        }
    }
    else if(p->type == TREE)
    {

    }
}

void loop_through_dir(char *path)
{
    DIR *directory = opendir(path);
    if(directory == NULL)
    {
        printf("Directory not opened\n");
        return;
    }
    /// 4-directory 8-file

    struct dirent *de;
    while((de = readdir(directory)) != NULL)
    {
        if(de->d_type ==DT_REG) 
        {
           nod *p; 
           p = malloc(sizeof(struct nod));
           p->type = BLOB;
           p->name = de->d_name;
           file_parser(p, de->d_name);
           p->data.entry = NULL;
           p->next = NULL;
           get_last_node(p);
        }
    }
    closedir(directory);
}

nod* sgit_init(char *path)
{
    head = malloc(sizeof(struct nod));
    head->name = "sal";
    head->type = TREE;
    head->next = NULL;
    head->data.entry = NULL;
    loop_through_dir(path);
    
    return head;
}