#include <stdio.h>
#include <stdint.h>
#include "objects/objects.h"
#include "sgit.h"
char *path = "/home/mateeiii11/Projects/sgit\0";
tree sgitTree;
int main()
{
    sgit_init(path);
    return 0;   
}