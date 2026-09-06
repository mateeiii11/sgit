#ifndef SGIT_H
#define SGIT_H

#include "objects.h"

nod* sgit_init(char *path);
void directory_concatenation(nod *p, nod *currentTree);
char *get_head_name(char *path);
#endif
