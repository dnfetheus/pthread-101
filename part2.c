#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>

#define SIZE 100000

int array[SIZE];

void a_remove(int index){
    for(int i = index; i < SIZE - 1; i++){
        array[i] = array[i + 1];
    }

    if(array[SIZE - 1] == 0){
        array[SIZE - 1] = 0;
    }
}

void *remove_even(){
    for(int i = 0; i < SIZE; i++){
        if(array[i] % 2 == 0){
            a_remove(i);
        }
    }
}

void *remove_prime(){
    int is_prime;

    for(int i = 0; i < SIZE; i++){
        is_prime = 1;

        for(int j = 2; j <= array[i]/2; j++){
            if(array[i] % j == 0){
                is_prime = 0;
                break;
            }
        }
        
        if(is_prime){
            a_remove(i);
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

    pthread_create(&threads[0], NULL, remove_even, NULL);
    pthread_create(&threads[1], NULL, remove_prime, NULL);

    pthread_exit(NULL);
}