#include <stdio.h>
#include <stdint.h>
#include "objects.h"
#include "sgit.h"
#include <stdlib.h>
#include "commands.h"
#include <string.h>
void terminal_parser(int argc, char **argv)
{
     if(argc == 2 && strcmp(argv[1], "init") == 0)	
	init();
     if(argc == 3 && strcmp(argv[1], "commit") == 0)
	commit_files(argv[2]);	
}

int main(int argc, char **argv)
{
    if(argc == 0) return 0;
    terminal_parser(argc, argv); 
    
    return 0;   
}
