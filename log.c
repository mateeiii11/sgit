#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void parse_hash(char *buffer, char *childHash, int space)
{
    int index = 0;
    int spaceCount = 0;
    for(; *buffer != '\0'; buffer++)
    {
        char c = *buffer;
        if(c == ' ') 
            spaceCount++;
        
        if(spaceCount == space && c >= '0' && c <= '9' )
                childHash[index++] = c;
    }
    childHash[index] = '\0';
}

void get_root_from_commit(const char commitHash[11], char *childHash, int space)
{
	size_t size = strlen(".sgit/objects/") + strlen(commitHash) + 1;
	char *pathBuffer = malloc(size);
	if(pathBuffer == NULL)
	{ 
		perror("Could not allocate enough memory");
		return;
	}
	snprintf(pathBuffer, size, ".sgit/objects/%s", commitHash);
	FILE *f = fopen(pathBuffer, "r");
	free(pathBuffer);
	if(f == NULL) return;

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
	fclose(f);
	if(space == 2)
		printf("%s\n", buffer);
	parse_hash(buffer, childHash,space);
	free(buffer);	
}

