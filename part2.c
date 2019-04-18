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

    if(array[SIZE - 1] != 0){
        array[SIZE - 1] = 0;
    }
}

void a_remove_mutex(int index){
    sem_wait(&mutex);
    a_remove(index);
    sem_post(&mutex);
}

void a_fulfill(){
    time_t t;

    srand((unsigned) time(&t));

    for(int i = 0; i < SIZE; i++){
        array[i] = (rand() % 100) + 1;
    }
}

void a_dump(int max){
    if(max > SIZE){
        max = SIZE;
    }

    printf("[ ");

    for(int i = 0; i < max; i++){
        printf("%d", array[i]);
        
        if(i < max - 1){
            printf(", ");
        }
    }

    printf(" ]\n");
}

void *remove_even(void *o){
    int n = (int) (intptr_t) o;

    for(int i = 0; i < SIZE; i++){
        if(array[i] != 0 && array[i] % 2 == 0){
            if(n == 0){
                a_remove(i--);
            }

            else{
                a_remove_mutex(i--);
            }
        }
    }
}

void *remove_prime(void *o){
    int is_prime, n = (int) (intptr_t) o;

    for(int i = 0; i < SIZE; i++){
        is_prime = 1;

        for(int j = 2; j * j <= array[i]; j++){
            if(array[i] % j == 0){
                is_prime = 0;
                break;
            }
        }

        if(is_prime == 1 && array[i] != 0){
            if(n == 0){
                a_remove(i--);
            }

            else{
                a_remove_mutex(i--);
            }

            continue;
        }
    }
}


int main(){
    pthread_t threads[2];
    a_fulfill();

    printf("Não usando semaforos\n");
    a_dump(20);
    pthread_create(&threads[0], NULL, remove_even, (void*) (intptr_t) 0);
    pthread_create(&threads[1], NULL, remove_prime, (void*) (intptr_t) 0);
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    a_dump(20);

    a_fulfill();

    printf("Usando semaforos\n");
    sem_init(&mutex, 1, 1);
    a_dump(20);
    pthread_create(&threads[0], NULL, remove_even, (void*) (intptr_t) 1);
    pthread_create(&threads[1], NULL, remove_prime, (void*) (intptr_t) 1);
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    a_dump(20);
    sem_destroy(&mutex);

    return 0;
}