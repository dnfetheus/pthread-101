#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 100000

int array[SIZE];

int main(){
    time_t t;

    srand((unsigned) time(&t));

    for(int i = 0; i < SIZE; i++){
        array[i] = (rand() % 100) + 1;
        printf("%d : %d\n", i, array[i]);
    }

    return 0;
}