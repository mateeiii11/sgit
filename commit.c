#include "commit.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "objects.h"
#include "hash.h"
#include <stdint.h>
#include <time.h>

uint32_t get_parent_hash(void)
{
	FILE *f = fopen(".sgit/HEAD", "r");
	if(f == NULL) return 0;
	uint32_t parent_hash = 0;
	if(fscanf(f, "%u", &parent_hash) != 1)
		parent_hash = 0;
	fclose(f);
	return parent_hash;
}

size_t create_commit_string(char **buffer, nod *head, char *message)
{
	time_t current_time = time(NULL);
	char time_string[26];
	ctime_r(&current_time, time_string);

	short root_count = get_int_count(head->hash);
	uint32_t parentHash = get_parent_hash();
	short parent_count = get_int_count(parentHash);

	size_t bufferSize = strlen("tree ") + root_count + 1 +
		            strlen("parent ") + parent_count + 1 +
			    strlen(time_string) + 
			    strlen("message ") + strlen(message) + 2;
	*buffer = malloc(bufferSize);
	if(*buffer == NULL) return 0;

	size_t writtenBytes = snprintf(*buffer, bufferSize, "tree %u\nparent %u\n%smessage %s\n", head->hash, parentHash, time_string, message);
	return writtenBytes;
}

void write_content_tofile(nod *currentNode)
{
	FILE *f;
	short count = get_int_count(currentNode->hash);
	size_t buffer_size = strlen(".sgit/objects/") + count + 1;
	char *buffer = malloc(buffer_size);
	if(buffer == NULL) return;
	strcpy(buffer, ".sgit/objects/");
	snprintf(buffer + strlen(buffer), buffer_size-strlen(buffer), "%u", currentNode->hash);
	f = fopen(buffer, "wbx");
	free(buffer);
	if(f == NULL) return;
	size_t bytes_written = fwrite(currentNode->data.file->content, 1, currentNode->data.file->size, f);
	if(bytes_written != currentNode->data.file->size)
	{
	   perror("Disk write error");
	   fclose(f);
	   return;
	}
	fclose(f);
}

void write_content_totree(nod *currentNode)
{
	FILE *f;
	short count = get_int_count(currentNode->hash);
	size_t buffer_size = strlen(".sgit/objects/") + count + 1;
	char *buffer = malloc(buffer_size);
	if(buffer == NULL) return;
	strcpy(buffer, ".sgit/objects/");
	snprintf(buffer + strlen(buffer), buffer_size-strlen(buffer), "%u", currentNode->hash);
	f = fopen(buffer, "wbx");
	free(buffer);
	if(f == NULL)
	   return;
	nod *nextFile = currentNode->data.entry;
	while(nextFile != NULL)
	{
	 	if(nextFile->type == BLOB)
			fprintf(f, "blob %u %s\n", nextFile->hash, nextFile->name);	
		else if(nextFile->type == TREE)
			fprintf(f, "tree %u %s\n", nextFile->hash, nextFile->name);	
	  	nextFile = nextFile->next;
	}
	fclose(f);
     
}
void create_blob_data(nod *currentNode)
{
     if(currentNode == NULL) return;
     if(currentNode->type == TREE && currentNode->data.entry != NULL)
    	create_blob_data(currentNode->data.entry);
     if(currentNode->next != NULL)
	     create_blob_data(currentNode->next);
     if(currentNode->type == BLOB)
	write_content_tofile(currentNode);	 
}

void create_tree_data(nod *currentNode)
{
     if(currentNode == NULL) return;
     if(currentNode->type == TREE)
     {
	 if(currentNode->data.entry != NULL)
		 create_tree_data(currentNode->data.entry);
	 write_content_totree(currentNode);

     }
     if(currentNode->next != NULL)
	     create_tree_data(currentNode->next);
}
void change_parent_head(uint32_t hash)
{
	FILE *f = fopen(".sgit/HEAD", "w");
	if(f == NULL) return;
	fprintf(f, "%u\n", hash);
	fclose(f);
}

void create_commit_data(nod *head, char *message)
{
	FILE *f;
	char *commitString = NULL;
	size_t size = create_commit_string(&commitString, head, message);
	if(size == 0 || commitString == NULL) return;
	uint32_t commit_hash = hash_string(commitString, size);
	short count = get_int_count(commit_hash);
	size_t buffer_size = strlen(".sgit/objects/") + count + 1;
	char *buffer = malloc(buffer_size);
	if(buffer == NULL) 
	{
		free(commitString);
		return;
	}
	strcpy(buffer, ".sgit/objects/");
	snprintf(buffer + strlen(buffer), buffer_size-strlen(buffer), "%u", commit_hash);
	f = fopen(buffer, "wbx");
	free(buffer);
	if(f == NULL) 
	{
		free(commitString);
		return;
	}
	size_t bytes_written = fwrite(commitString, 1, size, f);
	free(commitString);
	if(bytes_written != size)
	{
	   perror("Disk write error");
	   fclose(f);
	   return;
	}
	fclose(f);

	change_parent_head(commit_hash);
}

void commit_metadata(nod *tree_head, char *message)
{
	create_blob_data(tree_head);
	create_tree_data(tree_head);
	create_commit_data(tree_head, message);
}
