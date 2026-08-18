#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "hash.h"
#include "objects.h"
#include "sgit.h"
#include <stdlib.h>
char *path = "/home/mateeiii11/Projects/sgit\0";
int main()
{
    nod *head;  
    head = sgit_init(path);
    ///view(head);
    return 0;   
}