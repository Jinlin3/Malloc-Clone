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
struct node* head = (void*) memory; // we will edit the values of nodes with head

// mymalloc() function
void* mymalloc(size_t size, char *file, int line) 
{
    struct node* ptr; // we will traverse the list with ptr
    void* returnPtr; // for returning the metadata

    if (head->size == 0) {
        head->size = MEM_SIZE;
        head->inUse = 0;
        head->next = NULL;
    }

    ptr = head;

    // will set ptr to the start of the desired chunk of memory
    while (ptr->inUse == 1 || ptr->size < size && ptr->next != NULL) {
        ptr = ptr->next;
        printf("--traversing--\n");
    }
    printf("ptr->size: %zu\n", ptr->size);
    if (ptr->size == size) {
        //head = ptr;
        ptr->inUse = 1;
        returnPtr = (void*)(ptr++);
        return returnPtr;
    } else {
        struct node* temp = (void*)ptr + size + sizeof(struct node);
        temp->size = size;
        temp->inUse = 0;
        temp->next = NULL;
        ptr->next = temp;

        ptr->size = size + sizeof(struct node);
        printf("struct size: %zu\n", sizeof(struct node));
        ptr->inUse = 0;

        returnPtr = (void*)(ptr++);
        return returnPtr;
    }
}

// myfree() function
void myfree(void *ptr, char *file, int line)
{

}

int main(int argc, char **argv)
{
    char a = 'a';
    char* b = &a;
    mymalloc(10, b, 10);

    struct node* ptr = head;

    while (ptr != NULL) {
        printf("%zu -> ", ptr->size);
        ptr = ptr->next;
    }
    printf("NULL");
    return 0;
}