#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 100000

typedef struct {
    int size;
    int data[SIZE];
} array_t;

array_t array;
pthread_mutex_t mutex;

void array_remove(int index) {
    for (int i = index; i < array.size; i++) {
        array.data[i] = array.data[i + 1];
    }

    array.size--;
}

void array_fulfill() {
    srand((unsigned) time(NULL));
    array.size = SIZE;

    for (int i = 0; i < array.size; i++) {
        array.data[i] = (rand() % 100) + 1;
    }
}

void array_dump(int max) {
    if (max > array.size) {
        max = array.size;
    }

    printf("{ ");

    for (int i = 0; i < max; i++) {
        printf("%d", array.data[i]);
        
        if (i < max - 1) {
            printf(", ");
        }
    }

    printf(" }\n");
}

void *remove_even(void *o) {
    int *n = o;

    if (*n == 1) {
      pthread_mutex_lock(&mutex);
    }

    for (int i = 0; i < array.size; i++) {
        if (array.data[i] != 0 && array.data[i] % 2 == 0) {
            array_remove(i--);
        }
    }

    if (*n == 1) {
      pthread_mutex_unlock(&mutex);
    }
}

void *remove_prime(void *o) {
    int is_prime, *n = o;

    if (*n == 1) {
      pthread_mutex_lock(&mutex);
    }
    
    for (int i = 0; i < array.size; i++) {
        if (array.data[i] == 0) {
            continue;
        }

        is_prime = 1;

        for (int j = 2; j * j <= array.data[i]; j++) {
            if(array.data[i] % j == 0){
                is_prime = 0;
                break;
            }
        }

        if (is_prime == 1) {
            array_remove(i--);
        }
    }

    if (*n == 1) {
      pthread_mutex_unlock(&mutex);
    }
}


int main() {
    pthread_t threads[2];
    int option = 0;
    array_fulfill();

    printf("Without mutexes\n");
    printf("Part of generated array:\n");
    array_dump(50);
    printf("\n");
    pthread_create(&threads[0], NULL, remove_even, &option);
    pthread_create(&threads[1], NULL, remove_prime, &option);
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    printf("Part of array after executing threads:\n");
    array_dump(50);
    printf("\n\n");

    option = 1;
    array_fulfill();

    printf("With mutexes\n");
    pthread_mutex_init(&mutex, NULL);
    printf("Part of generated array:\n");
    array_dump(50);
    printf("\n");
    pthread_create(&threads[0], NULL, remove_even, &option);
    pthread_create(&threads[1], NULL, remove_prime, &option);
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);    
    printf("Part of array after executing threads:\n");
    array_dump(50);
    pthread_mutex_destroy(&mutex);

    return 0;
}
