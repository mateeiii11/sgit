#include <stdint.h>
#include <stdlib.h>
#include <string.h>

uint32_t hash(char *string)
{
    uint32_t hashNumber = 5381;
    char c;
    while((c = *(string++)) != 0)
        hashNumber = ((hashNumber << 5) + hashNumber) + c;
    return hashNumber;
}

char *hash_intToString(uint32_t hash)
{
    uint32_t buffer = hash;
    short size = 0;
    while(buffer != 0) 
    {
        buffer /= 10;
        size++;
    }
    char *string = malloc(size + 1);
    size = 0;
    uint32_t ogl = 0;
    while(hash != 0)
    {
        ogl = (ogl * 10) + (hash % 10);
        hash /= 10;
    }
    while(ogl != 0)
    {
        char c = '0' + (ogl % 10);
        ogl /= 10;
        string[size] = c;
        size++;
    }
    string[size] = '\0';
    return string;
}
