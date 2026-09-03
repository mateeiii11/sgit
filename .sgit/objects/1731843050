#include "commands.h"
#include <unistd.h>
#include "objects.h"
#include "sgit.h"
#include <stdio.h>
#include "objects.h"
#include <limits.h>
#include <stdlib.h>
#include "commit.h"
#include <time.h>
#include <sys/stat.h>

void view(nod *p)
{
    printf("Acesta este: %s cu hashul: %u\n",p->name, p->hash);
    if(p->type == TREE && p->data.entry != NULL) view(p->data.entry);
    if(p->next != NULL) view(p->next);
}
int create_hidden_folder(const char *folder_name)
{
    int status;
    #if defined(_WIN32)
    	status = _mkdir(folder_name);
	if(status == 0)
	{
		SetFileAttributesA(folder_name, FILE_ATTRIBUTE_HIDDEN);
	}
    #else
	status = mkdir(folder_name, 0755);
    #endif
    
    return status;
}

void init(void)
{     
    if(create_hidden_folder(".sgit") == 0)
    {
	if(create_hidden_folder(".sgit/objects") == -1)
	{
		perror("Could not create objects subdirectory");
		return;
	}

	FILE *fp;
	fp = fopen(".sgit/HEAD", "w");
	if(fp == NULL)
	{
		perror("Could not create HEAD file");
		return;
	}
	fprintf(fp, "");
	printf("%s\n", "Initialization is completed");
	fclose(fp);
    }
    else
    {
	    perror("Could not creat .sgit directory");
	    return;
    }
}
void commit_metadata(nod *tree_head, char *message)
{
	create_blob_data(tree_head);
	create_tree_data(tree_head);
	create_commit_data(tree_head, message);
}
void commit_files(char *message)
{ 
    char *path = getcwd(NULL, 0);
    nod *tree_head;  
    tree_head = sgit_init(path);
    commit_metadata(tree_head, message);
    printf("%s\n", "Commit initialized");
    free_tree_structure(tree_head);
}
