#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

char* file = "memtest.c";

int main(int argc, char** argv) {

    printMem();

    // An array with space for 10 void pointers
    void* array[10];

    // Allocating ten 20-byte blocks and storing the pointers into array
    for (int i = 0; i < 10; i++) {
        array[i] = mymalloc(20, file, 14);
        printMem();
    }

    // Allocating a 5000-byte block
    // Checking for error
    mymalloc(5000, file, 17);

    // Freeing all ten 20-byte blocks
    for (int i = 9; i >= 0; i--) {
        myfree(array[i], file, 24);
        myfree(array[i], file, 25);
        printMem();
    }

    // An array with space for 4 void pointers
    void* array2[4];

    // Filling up array with pointers for 100 byte blocks
    for (int i = 0; i < 4; i++) {
        array[i] = mymalloc(100, file, 32);
    }

    printMem();
    // Freeing block 1
    myfree(array[0], file, 35);
    printMem();
    // Freeing block 3
    myfree(array[2], file, 36);
    printMem();
    // Freeing block 2 ; checking if all three blocks have been coalesced
    myfree(array[1], file, 37);
    printMem();

    return 0;
}