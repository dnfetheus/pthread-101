#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

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

int main(){
    time_t t;

    srand((unsigned) time(&t));

    for(int i = 0; i < SIZE; i++){
        array[i] = (rand() % 100) + 1;
    }

    for(int i = 0; i < SIZE; i++){
        if(array[i] % 2 == 0){
            a_remove(array, i);
        }

        else{
            a_remove(array, i);
        }
    }

    return 0;
}