#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer = 0;
pthread_mutex_t mutex;
pthread_cond_t cond;

void *producer(void *arg) {
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex);
        while (buffer >= BUFFER_SIZE) {
            pthread_cond_wait(&cond, &mutex);
        }
        buffer++;
        printf("Producer = %d\n", buffer);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex);
        while (buffer <= 0) {
            pthread_cond_wait(&cond, &mutex);
        }
        buffer--;
        printf("Consumer = %d\n", buffer);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t producer_tid, consumer_tid;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_create(&producer_tid, NULL, producer, NULL);
    pthread_create(&consumer_tid, NULL, consumer, NULL);

    pthread_join(producer_tid, NULL);
    pthread_join(consumer_tid, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}
