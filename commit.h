#ifndef COMMIT_H
#define COMMIT_H

#include "objects.h"

void create_tree_data(nod *head);
void create_blob_data(nod *head);
void create_commit_data(nod *head, char *message);
void commit_metadata(nod *tree_head, char *message);
#endif
