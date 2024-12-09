#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 5000
#define BACKLOG 5
#define BUFFER_SIZE 1024

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_fd, BACKLOG);

    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);

    memset(buffer, 0, BUFFER_SIZE);
    recv(client_fd, buffer, BUFFER_SIZE, 0);
    printf("Received: %s\n", buffer);

    send(client_fd, "Message received", 16, 0);

    close(client_fd);
    close(server_fd);
    return 0;
}
