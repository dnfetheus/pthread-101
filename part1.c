#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdint.h>

void* hello_thread(void *i){
    int n = (int) (intptr_t) i;

    printf("Eu sou a thread%d\nMeu ID é %u pelo pthread_self()\nMeu ID é %u pelo gettid()\n\n", n, pthread_self(), syscall(SYS_gettid));
}

int main(){
    int num_threads;
    int result;

    printf("Digite o numero de threads que deseja executar\n");
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