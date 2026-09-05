#ifndef SGIT_H
#define SGIT_H

#include "objects.h"

nod* sgit_init(char *path);
void write_files_into_tree(char commitHash[11]);
#endif
