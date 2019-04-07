#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    int num_threads;

    printf("Enter with the number of threads you wish to create\n");
    scanf("%d", &num_threads);

    printf("Number of threads: %d\n", num_threads);

    return 0;
}