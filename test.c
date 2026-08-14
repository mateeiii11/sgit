#include <stdio.h>
#include <stdint.h>
#include "objects.h"

blob gitFile;
int main()
{
    file_parser(&gitFile, "test.txt");
    hash_blob(&gitFile);
    printf("%us\n", gitFile.hash);
    return 0;   
}