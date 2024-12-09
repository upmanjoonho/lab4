#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 5000
#define BACKLOG 5
#define BUFFER_SIZE 1024

void *client_handler(void *client_socket) {
    int client_fd = *(int *)client_socket;
    char buffer[BUFFER_SIZE];

    recv(client_fd, buffer, BUFFER_SIZE, 0);
    printf("Received: %s\n", buffer);
    send(client_fd, "Message received", 16, 0);

    close(client_fd);
    free(client_socket);
    return NULL;
}

int main() {
    int server_fd, *client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    pthread_t tid;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_fd, BACKLOG);

    while (1) {
        client_fd = malloc(sizeof(int));
        *client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
        printf("Client connected: %s\n", inet_ntoa(client_addr.sin_addr));

        pthread_create(&tid, NULL, client_handler, client_fd);
        pthread_detach(tid);
    }

    close(server_fd);
    return 0;
}
