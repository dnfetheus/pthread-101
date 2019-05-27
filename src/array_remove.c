#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <semaphore.h>

#define SIZE 100000

int array[SIZE];
sem_t mutex;

void a_remove(int index){
    for(int i = index; i < SIZE - 1; i++){
        array[i] = array[i + 1];
    }

    array[SIZE - 1] = 0;
}

void a_fulfill(){
    srand((unsigned) time(NULL));

    for(int i = 0; i < SIZE; i++){
        array[i] = (rand() % 100) + 1;
    }
}

void a_dump(int max){
    if(max > SIZE){
        max = SIZE;
    }

    printf("{ ");

    for(int i = 0; i < max; i++){
        printf("%d", array[i]);
        
        if(i < max - 1){
            printf(", ");
        }
    }

    printf(" }\n");
}

void *remove_even(void *o){
    int n = (int) (intptr_t) o;

    if(n == 1){
      sem_wait(&mutex);
    }

    for(int i = 0; i < SIZE; i++){
        if(array[i] != 0 && array[i] % 2 == 0){
            a_remove(i--);
        }
    }
    
    if(n == 1){
      sem_post(&mutex);
    }
}

void *remove_prime(void *o){
    int is_prime, n = (int) (intptr_t) o;

    if(n == 1){
      sem_wait(&mutex);
    }
    
    for(int i = 0; i < SIZE; i++){
        if(array[i] == 0){
            continue;
        }

        is_prime = 1;

        for(int j = 2; j * j <= array[i]; j++){
            if(array[i] % j == 0){
                is_prime = 0;
                break;
            }
        }

        if(is_prime == 1){
            a_remove(i--);
        }
    }

    if(n == 1){
      sem_post(&mutex);
    }
}


int main(){
    pthread_t threads[2];
    a_fulfill();

    printf("Without semaphores\n\n");
    printf("Generated array:\n");
    a_dump(50);
    pthread_create(&threads[0], NULL, remove_even, (void*) (intptr_t) 0);
    pthread_create(&threads[1], NULL, remove_prime, (void*) (intptr_t) 0);
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    printf("Array after using threads:\n");
    a_dump(50);

    a_fulfill();

    printf("With semaphores\n\n");
    sem_init(&mutex, 1, 1);
    printf("Generated array:\n");
    a_dump(50);
    pthread_create(&threads[0], NULL, remove_even, (void*) (intptr_t) 1);
    pthread_create(&threads[1], NULL, remove_prime, (void*) (intptr_t) 1);
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);    
    printf("Array after using threads:\n");
    a_dump(50);
    sem_destroy(&mutex);

    return 0;
}
