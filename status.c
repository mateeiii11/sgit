#include <stdio.h>
#include <stdlib.h>
#include "objects.h"
#include "sgit.h"
#include <string.h>
#include "hash.h"
#include <unistd.h>

#define UINT32_MAX_COUNT 10

void get_hash_root_tree(char *rootTree)
{
	FILE *f = fopen(".sgit/HEAD", "r");
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
	char *buffer = malloc(bufferSize);
	if(buffer == NULL) return;
	int res = snprintf(buffer, bufferSize, ".sgit/objects/%s", commitHash);
	if(res >= bufferSize)
	{
		free(buffer);
		return;
	}

	FILE *fp = fopen(buffer, "r");
	free(buffer);
	if(f == NULL) return;	
	char rootTreeBuffer[16];
	fgets(rootTreeBuffer, sizeof(rootTreeBuffer), f);
	if(rootTreeBuffer == NULL)
	{
		fclose(f);
		return;
	}
	int j = 0;
	for(int i = 0; i < strlen(rootTreeBuffer); i++)
	{
		if(rootTreeBuffer[i] >= '0' && rootTreeBuffer[i] <= '9')
			rootTree[j++] = rootTreeBuffer[i];
	}
	rootTree[j] = '\0';
	fclose(f);
}

void load_tree(char *currentTree, nod *tree)
{
	size_t size = strlen(".sgit/objects/") + strlen(currentTree) + 1;
	char *buffer = malloc(size);
	snprintf(buffer, size, ".sgit/objects/%s", currentTree);
	FILE *f = fopen(buffer, "r");
	if(f == NULL)
	{
		free(buffer);
		return;
	}	
	free(buffer);
	char *lineBuffer = NULL;
	size_t lineSize = 0;
	while(getline(&lineBuffer, &lineSize, f) != -1)
	{
		lineBuffer[strcspn(lineBuffer, "\r\n")] = '\0';

		char *type_t = strtok(lineBuffer, " ");
		char *hash_t = strtok(NULL, " ");
		char *name_t = strtok(NULL, " ");
		if(type_t == NULL || hash_t == NULL || name_t == NULL) continue;
		nod *p = calloc(1, sizeof(struct nod));
		if(strcmp(type_t, "blob") == 0)
		{
			p->type = BLOB;
			p->hash = string_to_int_hash(hash_t);
			p->name = strdup(name_t);
			p->next = NULL;
			p->data.file = NULL;
			directory_concatenation(p, tree);
		}
		else
		{
			p->type = TREE;
			p->hash = string_to_int_hash(hash_t);
			p->name = strdup(name_t);
			p->next = NULL;
			p->data.entry = NULL;
			load_tree(hash_t, p);
			directory_concatenation(p, tree);
		}
	}
	free(lineBuffer);
}

nod *create_temp_tree(char *currentTree)
{
	nod * tree = calloc(1, sizeof(struct nod));
 	tree->data.entry = NULL;
	tree->hash = string_to_int_hash(currentTree);
	tree->next = NULL;
	char *path = getcwd(NULL, 0);
	tree->name = get_head_name(path);
	free(path);
	tree->type = TREE;
	load_tree(currentTree, tree);
	return tree;
}

int get_state(nod *p, nod *search)
{
    if(p->type == TREE) 
    {
	
    }
}

void get_diff(nod *disk_tree, nod *tree, char *path)
{
	if(tree->type == TREE && tree->data.entry != NULL)
	{
		char *buffer = malloc(strlen(path) + 1 + strlen(tree->name) + 1);
		snprintf(buffer, "%s/%s", path, tree->name);
		get_diff(disk_tree, tree->data.entry, buffer);
		free(buffer);
	}
	if(p->next != NULL) getdiff(
}
