#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "hash.h"
#include "objects.h"
#include "sgit.h"
#include <stdlib.h>
char *path = "/home/mateeiii11/Projects/sgit\0";

void view(nod *p)
{
    if(p->type == BLOB)
        printf("%u\n", p->hash);
    if(p->type == TREE && p->data.entry != NULL) view(p->data.entry);
    if(p->next != NULL) view(p->next);
}

int main()
{
    nod *head;  
    head = sgit_init(path);
    view(head);
    return 0;   
}