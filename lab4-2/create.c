#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *print_message(void *arg) {
    int thread_num = *((int *)arg);
    printf("Thread %d: Hello!\n", thread_num);
    sleep(1);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[3];
    int thread_args[3];
    int status;

    for (int i = 0; i < 3; i++) {
        thread_args[i] = i + 1;
        status = pthread_create(&threads[i], NULL, print_message, &thread_args[i]);
        if (status != 0) {
            exit(1);
        }
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("end\n");
    return 0;
}
