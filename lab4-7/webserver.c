#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/wait.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_client(int client_fd) {
    char buffer[BUFFER_SIZE];
    char method[10], path[50], protocol[20];
    int read_size;

    read_size = read(client_fd, buffer, BUFFER_SIZE - 1);
    if (read_size <= 0) {
        close(client_fd);
        return;
    }

    buffer[read_size] = '\0';
    sscanf(buffer, "%s %s %s", method, path, protocol);

    if (strcmp(method, "GET") == 0) {
        if (strcmp(path, "/") == 0) {
            write(client_fd, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n", 45);
            write(client_fd, "<html><body><h1>Welcome to Webserver</h1></body></html>", 56);
        } else if (strcmp(path, "/hello") == 0) {
            FILE *fp = popen("./hello", "r");
            if (fp) {
                char output[BUFFER_SIZE];
                write(client_fd, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n", 46);
                while (fgets(output, sizeof(output), fp)) {
                    write(client_fd, output, strlen(output));
                }
                pclose(fp);
            }
        } else {
            write(client_fd, "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\n", 52);
            write(client_fd, "404 Not Found", 13);
        }
    } else if (strcmp(method, "POST") == 0) {
        char *body = strstr(buffer, "\r\n\r\n");
        if (body) {
            body += 4;
            write(client_fd, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n", 46);
            write(client_fd, "POST Data Received:\n", 20);
            write(client_fd, body, strlen(body));
        }
    }

    close(client_fd);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_fd, 5);

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
        if (fork() == 0) {
            close(server_fd);
            handle_client(client_fd);
            exit(0);
        } else {
            close(client_fd);
            waitpid(-1, NULL, WNOHANG);
        }
    }

    close(server_fd);
    return 0;
}
