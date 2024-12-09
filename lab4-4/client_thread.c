#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NUM_CLIENTS 3
#define MAX_MESSAGE_LENGTH 256

pthread_mutex_t mutex;
pthread_cond_t cond;

char message[MAX_MESSAGE_LENGTH];
int message_ready = 0;

void *server_thread(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);

        while (!message_ready) {
            pthread_cond_wait(&cond, &mutex);
        }

        printf("messege: \"%s\"\n", message);
        message_ready = 0;
        pthread_cond_broadcast(&cond);

        pthread_mutex_unlock(&mutex);

        if (strcmp(message, "exit") == 0) break;
    }
    return NULL;
}

void *client_thread(void *arg) {
    int id = *((int *)arg);
    char local_message[MAX_MESSAGE_LENGTH];

    while (1) {
        pthread_mutex_lock(&mutex);

        while (message_ready) {
            pthread_cond_wait(&cond, &mutex);
        }

        if (strcmp(message, "exit") == 0) {
            pthread_mutex_unlock(&mutex);
            break;
        }

        printf("Client %d: ", id);
        fgets(local_message, MAX_MESSAGE_LENGTH, stdin);
        local_message[strcspn(local_message, "\n")] = '\0';

        strncpy(message, local_message, MAX_MESSAGE_LENGTH);
        message_ready = 1;

        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);

        if (strcmp(local_message, "exit") == 0) break;
    }
    return NULL;
}

int main() {
    pthread_t server;
    pthread_t clients[NUM_CLIENTS];
    int client_ids[NUM_CLIENTS];

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_create(&server, NULL, server_thread, NULL);

    for (int i = 0; i < NUM_CLIENTS; i++) {
        client_ids[i] = i + 1;
        pthread_create(&clients[i], NULL, client_thread, &client_ids[i]);
    }

    pthread_join(server, NULL);

    for (int i = 0; i < NUM_CLIENTS; i++) {
        pthread_join(clients[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    printf("end.\n");
    return 0;
}
