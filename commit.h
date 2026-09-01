#ifndef COMMIT_H
#define COMMIT_H

#include "objects.h"

commit *create_commit(nod *head_input, commit *parent_input, char *message_input);
void free_commit_structure(commit *c);
#endif
