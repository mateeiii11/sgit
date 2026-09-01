#include "commands.h"
#include <unistd.h>
#include "sgit.h"
#include <stdio.h>
#include "objects.h"
#include <limits.h>
#include <stdlib.h>
#include "commit.h"
#include <time.h>

static commit *commit_head = NULL;

void view(nod *p)
{
    printf("Acesta este: %s cu hashul: %u\n",p->name, p->hash);
    if(p->type == TREE && p->data.entry != NULL) view(p->data.entry);
    if(p->next != NULL) view(p->next);
}
void commit_sal(commit *c)
{
	printf("Commit message: %s\n", c->message);
	if(c->head_tree != NULL) view(c->head_tree);
	if(c->parent != NULL) commit_sal(c->parent);
}

void init()
{     
    printf("%s\n", "have to create files");
}

void commit_files(char *message)
{ 
    char *path = getcwd(NULL, 0);
    nod *tree_head;  
    commit *c;
    tree_head = sgit_init(path);
    c = create_commit(tree_head, commit_head, message);
    commit_head = c;
    commit_sal(c);
}
