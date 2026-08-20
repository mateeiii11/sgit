#ifndef HASH_H
#define HASH_H

#include <stdint.h>
#include <stdlib.h>
uint32_t hash_string(char *content, size_t size);
short get_int_count(uint32_t hash);
#endif