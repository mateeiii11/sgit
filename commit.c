#include "commit.h"
#include <stdio.h>
#include "objects.h"
#include <time.h>
#include <string.h>
#include "objects.h"

commit *create_commit(nod *head_input, commit *parent_input, char *message_input)
{
     commit *c;
     time_t current_time = time(NULL);
     c = malloc(sizeof(struct commit));
     c->message = strdup(message_input);
     ctime_r(&current_time, c->time);
     c->parent = parent_input;
     c->head_tree = head_input;
}

void free_commit_structure(commit *c)
{
     if(c == NULL) return;
     free_tree_structure(c->head_tree);
     if(c->message != NULL) 
	free(c->message);
     free(c);     
     if(c->parent != NULL) free_commit_structure(c->parent);

}
