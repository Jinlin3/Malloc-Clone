#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

// Linked list structure for metadata
struct node {
    size_t size;
    int inUse; // 0 = free ; 1 = in-use
    struct node* next;
};

struct node* head = (struct node*) memory; // head points to the beginning of memory

// mymalloc() function
void* mymalloc(size_t size, char *file, int line) 
{
    void* returnPtr;
    int currentLoc = 0;
    int nextLoc;
    size_t chunkSize = size + sizeof(struct node*); // set equal to the amount of bytes desired + amount needed for metadata
    
    // checks if size == 0
    if (size == 0) {
        printf("Error at %s on line %i | Cannot allocate 0 bytes!\n", file, line);
        returnPtr = NULL;
        return returnPtr;
    }

    // checks if memory has been initialized
    if (head->size == 0) {
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
        printf("Error at %s on line %i | Not enough memory to store %d bytes!\n", file, line, (int)chunkSize);
        returnPtr = NULL;
        return returnPtr;
    }

    if (ptr->size > chunkSize) {
        struct node* new = ptr + chunkSize; // new node for splitting
        new->inUse = 0;
        if (ptr->next != NULL) {
            nextLoc = currentLoc + ptr->size;
            new->next = ptr->next;
            new->size = MEM_SIZE - currentLoc - chunkSize - (MEM_SIZE - nextLoc);
        } else {
            new->next = NULL;
            new->size = MEM_SIZE - currentLoc - chunkSize;
        }
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
// will use guard clause-ish techniques
void myfree(void *ptr, char *file, int line)
{
    // first determine whether the ptr is a valid ptr or not
    // compare addresses of parameter ptr and the &traverse + sizeof(traverse)
    struct node* last = head;
    struct node* traverse = head;
    int counter = 0;

    // while loop stops if traverse and any nodes match
    while (traverse != NULL) {
        if (ptr == traverse + sizeof(traverse)) {
            break;
        } else {
            last = traverse;
            traverse = traverse->next;
            counter++;
        }
    }
    // checks if the loop ran all the way and the current ptr still doesn't match
    // this means that there are no matching nodes and the ptr given did not come from mymalloc()
    if ((traverse->next == NULL) && (ptr != (traverse + sizeof(traverse)))) {
        printf("Error at %s on line %i | Pointer given is not a pointer given by mymalloc()\n", file, line);
        return;
    }
    // at this point the pointer given is a pointer given by mymalloc()
    // now we check if the chunk has already been freed
    if (traverse->inUse == 0) {
        printf("Error at %s on line %i | Chunk has already been freed\n", file, line);
        return;
    }
    // has passed all guard clauses
    // so free current chunk
    traverse->inUse = 0;

    // procedure to coalesce free chunks:
    /*
        --IF LAST CHUNK IS FREE--
        1. if last chunk is also free, set a pointer to that chunk
        2. then traverse through chunks until the next chunk is not free
        3. then merge everything in between

        --IF NEXT CHUNK IS FREE--
        1. merge current chunk and next chunk
    */

    if (last->inUse == 0 && counter != 0) {
        struct node* temp = traverse;
        while (temp->inUse == 0 && temp != NULL) {
            last->size = last->size + temp->size;
            last->next = temp->next;
            temp = temp->next;
        }
    }

    if (traverse->next->inUse == 0) {
        traverse->size = traverse->size + traverse->next->size;
        traverse->next = traverse->next->next;
    }

    return;
}

void printMem()
{
    struct node* ptr = head;
    if (ptr->size == MEM_SIZE) {
        printf("%i|%i -> NULL\n", ptr->inUse, MEM_SIZE);
        return;
    }
    while (ptr != NULL) {
        printf("%i|%d -> ", ptr->inUse, (int)ptr->size);
        ptr = ptr->next;
    }
    printf("NULL\n");
    return;
}