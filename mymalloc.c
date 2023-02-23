#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

// Linked list structure for metadata
struct node {
    size_t size;
    int inUse; // 0 = free ; 1 = in-use
    struct node* next;
};

// This is the global array
static char memory[MEM_SIZE];
struct node* head = (struct node*) memory; // we will edit the values of nodes with head

// mymalloc() function
void* mymalloc(size_t size, char *file, int line) 
{
    void* returnPtr;
    int currentLoc = 0;
    size_t chunkSize = size + sizeof(struct node*); // set equal to the amount of bytes desired + amount needed for metadata
    
    // checks if size == 0
    if (size == 0) {
        printf("Cannot allocate 0 bytes!\n");
        returnPtr = NULL;
        return returnPtr;
    }

    // checks if memory has been initialized
    if (head->size == 0) {
        printf("--first initialization--\n");
        head->size = MEM_SIZE;
        head->inUse = 0;
        head->next = NULL;
    }

    struct node* ptr = head; // pointer for traversing through LL

    // sets ptr equal to a valid chunk in the array
    while (ptr->next != NULL) {
        if (ptr->inUse == 0 && ptr->size >= chunkSize) {
            break;
        } else {
            currentLoc = currentLoc + ptr->size;
            ptr = ptr->next;
        }
    }

    /*
    3 cases at this stage:
    1. The current pointer size is greater than the needed size, thus requiring us to divide the last chunk into 2.
    2. The current pointer size is equal to the needed size, making it simple.
    3. The current pointer size is less than the needed size, meaning there are no available chunks.
    */
    if (ptr->size < chunkSize) {
        printf("Not enough memory to store %zu bytes.\n", chunkSize);
        returnPtr = NULL;
        return returnPtr;
    }

    if (ptr->size > chunkSize) {
        struct node* new = ptr + chunkSize;
        new->inUse = 0;
        new->size = MEM_SIZE - currentLoc - chunkSize;
        new->next = NULL;
        ptr->inUse = 1;
        ptr->size = chunkSize;
        ptr->next = new;

        returnPtr = ptr + sizeof(struct node*);
    } else {
        ptr->inUse = 1;
        returnPtr = ptr + sizeof(struct node*);
    }
    return returnPtr;
}

// myfree() function
void myfree(void *ptr, char *file, int line)
{

}

void printMem()
{
    struct node* ptr = head;
    while (ptr != NULL) {
        printf("%i|%zu -> ", ptr->inUse, ptr->size);
        ptr = ptr->next;
    }
    printf("NULL\n");
    return;
}

int main(int argc, char **argv)
{
    char a = 'a';
    char* b = &a;
    mymalloc(100, b, 10);
    mymalloc(200, b, 10);
    mymalloc(10, b, 10);
    printMem();
    return 0;
}