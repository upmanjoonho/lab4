#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2
#define NUM_ITEMS 10

typedef struct {
    int buffer[BUFFER_SIZE];
    int in, out, count;
    pthread_mutex_t mutex;
    pthread_cond_t not_full;
    pthread_cond_t not_empty;
} bounded_buffer_t;

bounded_buffer_t bb = {{0}, 0, 0, 0, PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER, PTHREAD_COND_INITIALIZER};

void insert_item(int item) {
    pthread_mutex_lock(&bb.mutex);

    while (bb.count == BUFFER_SIZE) {
        pthread_cond_wait(&bb.not_full, &bb.mutex);
    }

    bb.buffer[bb.in] = item;
    printf("%d by %lu\n", item, pthread_self());
    bb.in = (bb.in + 1) % BUFFER_SIZE;
    bb.count++;

    pthread_cond_signal(&bb.not_empty);
    pthread_mutex_unlock(&bb.mutex);
}

int remove_item() {
    int item;

    pthread_mutex_lock(&bb.mutex);

    while (bb.count == 0) {
        pthread_cond_wait(&bb.not_empty, &bb.mutex);
    }

    item = bb.buffer[bb.out];
    printf("\tConsumed: %d by %lu\n", item, pthread_self());
    bb.out = (bb.out + 1) % BUFFER_SIZE;
    bb.count--;

    pthread_cond_signal(&bb.not_full);
    pthread_mutex_unlock(&bb.mutex);

    return item;
}

void* producer(void* arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        int item = rand() % 100;
        insert_item(item);
        sleep(1);
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        remove_item();
        sleep(2);
    }
    return NULL;
}

int main() {
    pthread_t producers[NUM_PRODUCERS], consumers[NUM_CONSUMERS];

    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_create(&producers[i], NULL, producer, NULL);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_create(&consumers[i], NULL, consumer, NULL);
    }

    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producers[i], NULL);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumers[i], NULL);
    }

    printf("end.\n");
    return 0;
}
