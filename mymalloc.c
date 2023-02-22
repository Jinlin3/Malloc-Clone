#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

// Linked list structure for metadata
struct Node {
    struct Node* next;
    int payload;
    int inUse; // 0 = free ; 1 = in-use
};

// This is the global array
static char memory[MEM_SIZE];

// mymalloc() function
void* mymalloc(size_t size, char *file, int line) {

    struct Node *start; // start pointer
    struct Node *ptr; // traversing pointer
    struct Node *separation; // separation pointer

    int loc = 0; //location value
    int placed = 0; //boolean to check if memory has been allocated

    void* returnPtr; //pointer used to return

    if (size == 0) { //checks if user input is invalid
        printf("Cannot allocate 0 bytes.");
        return 0;
    }

    start = (struct Node*) memory;

    if (memory[0] == 0) { //if malloc wasn't called yet, a start pointer will be created
        printf("initializing first malloc...\n");
        start->payload = MEM_SIZE;
        start->inUse = 0;
        memory[0] = 1;
    }

    ptr = start;

    while (placed == 0) {
        if (ptr->inUse == 0) {
            ptr->payload = size;
            ptr->inUse = 1;

            separation = (struct Node*) &memory[loc + size]; //sets next node's location
            separation->payload = MEM_SIZE - loc - size; //sets next node's payload
            separation->inUse = 0; //sets the status to free

            ptr->next = separation; //links the two pointers

            printf("%lu\n", loc + size);
            placed = 1;
        } else {
            loc = loc + ptr->payload;
            ptr = ptr->next;
            printf("traversing...\n");
        }
    }

    return returnPtr;
}

// myfree() function
void myfree(void *ptr, char *file, int line) {

}

int main(int argc, char **argv) {
    char* a = "a";
    printf("first malloc\n");
    mymalloc(10, a, 10);
    printf("second malloc\n");
    mymalloc(50, a, 10);
    return 0;
}