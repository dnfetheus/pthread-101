#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdint.h>

void* hello_thread(void *i){
    int n = (int) (intptr_t) i;

    printf("Eu sou a thread%d e meu ID é %u pelo pthread_self()\n", n, pthread_self());
    printf("Eu sou a thread%d e meu ID é %u pelo gettid()\n\n", n, syscall(SYS_gettid));

    pthread_exit(NULL);
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

    pthread_exit(NULL);
}