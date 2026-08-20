#include <stdint.h>
#include <math.h>

uint32_t hash_string(char *string)
{
    uint32_t hashNumber = 5381;
    char c;
    while((c = *(string++)) != 0)
        hashNumber = ((hashNumber << 5) + hashNumber) + c;
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