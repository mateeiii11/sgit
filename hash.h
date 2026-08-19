#ifndef HASH_H
#define HASH_H

#include <stdint.h>
uint32_t hash_string(char *string);
char *hash_intToString(uint32_t hash_int);

#endif