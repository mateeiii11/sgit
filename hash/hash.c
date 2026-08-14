#include <stdint.h>

uint32_t hash(char *string)
{
    uint32_t hashNumber = 5381;
    char c;
    while((c = *(string++)) != 0)
        hashNumber = ((hashNumber << 5) + hashNumber) + c;
    return hashNumber;
}
