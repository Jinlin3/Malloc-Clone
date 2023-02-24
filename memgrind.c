#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mymalloc.h"

char* file = "memgrind.c";

void testA() {

    for (int j = 0; j < 120; j++) {
        void* test1 = mymalloc(1, file, 11);
        myfree(test1, file, 12);
    }
    
    return;
}

void testB() {

    void* array[120];
    for (int i = 0; i < 120) {
        array[i] = mymalloc(1, file, 22);
    }
    for (int j = 0; j < 120) {
        myfree(array[j], file, 25);
    }

}

void testC() {
    
}

int main(int argc, char** argv) {

    float testA = testA();
    printf("Test A time in microseconds: %f\n", testA);

    return 0;
}