#include <stdint.h>
#include <stdlib.h>
uint32_t hash_string(char *content, size_t size)
{
    uint32_t hashNumber = 5381;
    unsigned char c;
    for(size_t i = 0; i < size; i++)
    { 
        c = content[i];
        hashNumber = ((hashNumber << 5) + hashNumber) + c;
    }
    return hashNumber;
}
short get_int_count(uint32_t hash)
{
    if(hash == 0) return 1;
    short size = 0;
    while(hash != 0)
    {
        size++;
        hash /= 10;
    }
    return size;
}