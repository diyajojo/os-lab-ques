SERVER SIDE :

#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {

    int server_socket, client_socket;
    struct sockaddr_in server_addr;
    char buffer[100];

    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

    listen(server_socket, 1);
    printf("Server waiting...\n");

    client_socket = accept(server_socket, NULL, NULL);

    read(client_socket, buffer, sizeof(buffer));
    printf("Client says: %s\n", buffer);

    send(client_socket, "Hello Client", 12, 0);

    close(client_socket);
    close(server_socket);

}

CLIENT SIDE : 

#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

int main() {

    int sock;
    struct sockaddr_in server;
    char message[] = "Hello Server";
    char buffer[100];

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr*)&server, sizeof(server));

    send(sock, message, strlen(message), 0);

    read(sock, buffer, sizeof(buffer));
    printf("Server replied: %s\n", buffer);

    close(sock);

}