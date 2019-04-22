#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdint.h>

void* hello_thread(void *i){
    int n = (int) (intptr_t) i;

    printf("I'm thread%d\nMy ID is %lu according to pthread_self()\nMy ID is %lu according to gettid()\n\n", n, pthread_self(), syscall(SYS_gettid));
}

int main(){
    int num_threads;
    int result;

    printf("Enter with the number of threads to execute\n");
    scanf("%d", &num_threads);

    pthread_t threads[num_threads];

    for(int i = 0; i < num_threads; i++){
        pthread_create(&threads[i], NULL, hello_thread, (void*) (intptr_t) (i + 1));
    }

    for(int i = 0; i < num_threads; i++){
        pthread_join(threads[i], NULL);
    }

    return 0;
}