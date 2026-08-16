#include "sgit.h"
#include "objects/objects.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void loop_through_dir(char *path, tree *sgitTree)
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
        if(strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0 
    || strcmp(de->d_name, ".git") == 0) continue;
        if(de->d_type == '8')
        {
            
        }
    }

    closedir(directory);
}

tree sgit_init(char *path)
{
    tree *sgitTree = NULL;
    sgitTree = malloc(sizeof(struct tree));
    sgitTree->depth = 0;
    loop_through_dir(path, sgitTree);
    return *sgitTree;
}