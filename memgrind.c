#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include "mymalloc.h"

char* file = "memgrind.c";

float testA() {

    struct timeval start, end;

    gettimeofday(&start, NULL);

    for (int j = 0; j < 120; j++) {
        void* test1 = mymalloc(1, file, 17);
        myfree(test1, file, 18);
    }

    gettimeofday(&end, NULL);
    
    return (float)((end.tv_sec - start.tv_sec) * 10000000 + (end.tv_usec - start.tv_usec) * 0.000001);
}

float testB() {

    struct timeval start, end;

    gettimeofday(&start, NULL);

    void* array[120];
    for (int i = 0; i < 120; i++) {
        array[i] = mymalloc(1, file, 34);
    }
    for (int j = 0; j < 120; j++) {
        myfree(array[j], file, 37);
    }

    gettimeofday(&end, NULL);
    
    return (float)((end.tv_sec - start.tv_sec) * 10000000 + (end.tv_usec - start.tv_usec) * 0.000001);
}

float testC() {
    

    struct timeval start, end;
    int mallocCounter = 0;
    int currentIndex = 0;
    srand(time(NULL));
    void* array[10];
    
    gettimeofday(&start, NULL);

    while (mallocCounter != 120) {
        int random = rand() % 2 + 1;
        if (random == 1) {
            array[currentIndex] = mymalloc(1, file, 59);
            mallocCounter++;
            currentIndex++;
        } else {
            myfree(array[currentIndex - 1], file, 63);
            currentIndex--;
        }
    }

    for (int i = currentIndex - 1; i >= 0; i--) {
        myfree(array[currentIndex - 1], file, 69);
    }

    gettimeofday(&end, NULL);

    return (float)((end.tv_sec - start.tv_sec) * 10000000 + (end.tv_usec - start.tv_usec) * 0.000001);
}

int main(int argc, char** argv) {

    float aSum = 0;
    float bSum = 0;
    float cSum = 0;

    for (int i = 0; i < 50; i++) {
        aSum += testA();
        bSum += testB();
        cSum += testC();
    }
    printf("Test A time in microseconds: %.8f\n", aSum);
    printf("Test B time in microseconds: %.8f\n", bSum);
    printf("Test C time in microseconds: %.8f\n", cSum);

    return 0;
}