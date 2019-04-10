#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>

#define SIZE 100000

int array[SIZE];

void a_remove(int array[], int index){
    for(int i = index; i < SIZE - 1; i++){
        array[i] = array[i + 1];
    }

    if(array[SIZE - 1] == 0){
        array[SIZE - 1] = 0;
    }
}

void *iterate_array(void *m){
    int mode = (int) (intptr_t) m;
    for(int i = 0; i < SIZE; i++){
        if(mode == 0 && array[i] % 2 == 0){
            a_remove(array, i);
        }

        else if(mode == 1 && array[i] % 2 != 0){
            a_remove(array, i);
        }
    }
}

int main(){
    time_t t;
    pthread_t threads[2];

    srand((unsigned) time(&t));

    for(int i = 0; i < SIZE; i++){
        array[i] = (rand() % 100) + 1;
    }

    pthread_create(&threads[0], NULL, iterate_array, (void*) (intptr_t) 0);
    pthread_create(&threads[1], NULL, iterate_array, (void*) (intptr_t) 1);

    pthread_exit(NULL);
}