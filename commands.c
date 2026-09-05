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
#include <string.h>
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
    free(path);
    commit_metadata(tree_head, message);
    printf("%s\n", "Commit initialized");
    free_tree_structure(tree_head);
}

void parse_hash(char *buffer, char *childHash)
{
	int index = 0;
	int spaceCount = 0;
	for(; *buffer != '\0'; buffer++)
	{
		char c = *buffer;
		if(c == ' ') spaceCount++;
		if(spaceCount == 2 && c >= '0' && c <= '9')
			childHash[index++] = c;
	}
	childHash[index] = '\0';
}

void sgitLog(const char commitHash[12])
{
	size_t size = strlen(".sgit/objects/") + strlen(commitHash) + 1;
	char *pathBuffer = malloc(size);
	if(pathBuffer == NULL)
	{ 
		perror("Could not allocate enough memory");
		return;
	}
	int result = snprintf(pathBuffer, size, ".sgit/objects/%s", commitHash);
	if(result >= size) return;
	FILE *f = fopen(pathBuffer, "r");
	if(f == NULL)
	{
		perror("Could not open HEAD file");
		free(pathBuffer);
		return;
	}

	free(pathBuffer);
	fseek(f, 0, SEEK_END);
	size_t bufferSize = ftell(f);
	fseek(f, 0, SEEK_SET);
	char *buffer = malloc(bufferSize + 1);
	if(buffer == NULL) 
	{
		fclose(f);
		return;
	}
	size_t bytesRead = fread(buffer, 1, bufferSize, f);
	buffer[bytesRead] = '\0';
	printf("%s\n", buffer);
	char childHash[12];
	parse_hash(buffer, childHash);
	free(buffer);	
	fclose(f);
	if(strcmp(childHash, "0") != 0) sgitLog(childHash);
}

get_hash_root_tree(char *rootTree)
{
	FILE *f = fopen(".sgit/HEAD", "r")
	if(f == NULL) return;
	char commitHash[11];
	int result = fscanf(f, "%s", commitHash);
	if(result != 1)
	{
		fclose(f);
		return;
	}
	fclose(f);

	size_t bufferSize = strlen(".sgit/objects/") + strlen(commitHash) + 1;
	char *buffer = malloc(size);
	if(buffer == NULL) return;
	int res = snprintf(buffer, size, ".sgit/objects/%s", commitHash);
	if(res >= size)
	{
		free(buffer);
		return;
	}

	FILE *fp = fopen(buffer, "r");
	free(buffer);
	if(f == NULL) return;
	
}

void status(void)
{
    char *path = getcwd(NULL, 0);
    nod *disk_tree;  
    disk_tree = sgit_init(path);
    free(path);
    char rootTree[11];
    get_hash_root_tree(rootTree);
    free_tree_structure(disk_tree);
}
