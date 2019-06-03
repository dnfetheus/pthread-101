#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdint.h>

typedef struct ext_thread{
    int position;
    pthread_t thread;
} ext_thread_t;

void* hello_thread(void *i){
    int *n = i;
    printf("I'm thread%02d\nMy ID is %lu according to pthread_self()\nMy ID is %lu according to gettid()\n\n", *n, pthread_self(), syscall(SYS_gettid));
}

int main(){
    int num_threads, i;

    printf("Enter with the number of threads to execute\n");
    scanf("%d", &num_threads);

    ext_thread_t threads[num_threads];

    for(i = 0; i < num_threads; i++){
        threads[i].position = i + 1;
        pthread_create(&threads[i].thread, NULL, hello_thread, &threads[i].position);
    }

    for(int i = 0; i < num_threads; i++){
        pthread_join(threads[i].thread, NULL);
    }

    return 0;
}