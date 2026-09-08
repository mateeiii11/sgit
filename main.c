#include <stdio.h>
#include <stdint.h>
#include "objects.h"
#include "sgit.h"
#include <stdlib.h>
#include "commands.h"
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <errno.h>

int directory_existence(const char *path)
{
	struct stat info;
	if(stat(path, &info) != 0) return 0;
	return S_ISDIR(info.st_mode);
}

void terminal_parser(int argc, char **argv)
{
     if(argc < 2) return;
     if(strcmp(argv[1], "init") == 0)	
     {
	init();
	return;
     }

     if(directory_existence(".sgit") == 0)
     {
	     printf(".sgit not initialized, run sgit init first\n");
	     return;
     }
     if(argc == 3 && strcmp(argv[1], "commit") == 0)
	commit(argv[2]);	
     else if(argc == 2 && strcmp(argv[1], "log") == 0)
     {
				
		FILE *f = fopen(".sgit/HEAD", "r");
		if(f == NULL)
		{
			perror("Could not open HEAD file");
			return;
		}
		char buffer[11];

		if(fscanf(f, "%s", buffer) != 1)
		{
			fclose(f);
			return;
		}
		fclose(f);
		printf("\n");
		sgitLog(buffer);
     }
     else if(argc == 2 && strcmp(argv[1], "status") == 0)
	     status();
     else if(argc == 3 && strcmp(argv[1], "checkout") == 0)
	     checkout(argv[2]);
}

int main(int argc, char **argv)
{
    if(argc == 0) return 0;
    terminal_parser(argc, argv); 
    
    return 0;   
}
