#ifndef PARTITION_H
#define PARTITION_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <pthread.h>
#include <stddef.h>

#define PARTITION_MAX (1024 * 1024)

// Partition memory allocation based on types
#define palloc(SIZE, TYPE) __palloc(SIZE, #TYPE)

// Free memory based on types
#define pfree(PTR, TYPE) __pfree(PTR, #TYPE)

// Displays memory in partition
#define printpart(TYPE, MAX) __printpart(#TYPE, MAX)

// Internal function to allocate memory in the integer heap
void *__int_malloc(size_t sz);

// Internal function to allocate memory in the character heap
void *__char_malloc(size_t sz);

// Internal function to allocate memory in the float heap
void *__float_malloc(size_t sz);

// Internal function to allocate memory in the generic heap
void *__generic_malloc(size_t sz);

// Internal function to allocate memory in type separated heaps
void *__palloc(size_t sz, const char *type);

// Internal function to clear memory in a heap
void __pfree(void *mem, const char *type);

// Internal function to print partition contents
void __printpart(const char *type, int max);

#endif