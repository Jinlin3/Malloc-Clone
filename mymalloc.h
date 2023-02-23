// Prevents double declaration
#ifndef MYMALLOC_H
#define MYMALLOC_H
// Important libraries
#include <stdlib.h>
#include <stdio.h>

#define malloc(s) mymalloc(s, __FILE__, __LINE__)
#define free(p) myfree(p, __FILE__, __LINE__)

#define MEM_SIZE 4096

void* mymalloc(size_t size, char *file, int line);
void myfree(void *ptr, char *file, int line);
void printMem();

// MYMALLOC_H
#endif