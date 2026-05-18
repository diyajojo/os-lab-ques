// client code:
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int s;
    struct sockaddr_in client;
    socklen_t len = sizeof(client);

    char buffer[100];

    s = socket(AF_INET, SOCK_DGRAM, 0);

    client.sin_family = AF_INET;
    client.sin_port = htons(3000);
    client.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Enter message: ");
    fgets(buffer, sizeof(buffer), stdin);

    sendto(s, buffer, strlen(buffer) + 1, 0,
           (struct sockaddr*)&client, len);

    recvfrom(s, buffer, sizeof(buffer), 0,
             (struct sockaddr*)&client, &len);

    printf("Server reply: %s\n", buffer);

    close(s);

    return 0;
}

//server code:
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int s;
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    char buffer[100];

    s = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(3000);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(s, (struct sockaddr*)&server, sizeof(server));

    recvfrom(s, buffer, sizeof(buffer), 0,
             (struct sockaddr*)&client, &len);

    printf("Client sent: %s\n", buffer);

    printf("Enter reply: ");
    fgets(buffer, sizeof(buffer), stdin);

    sendto(s, buffer, strlen(buffer) + 1, 0,
           (struct sockaddr*)&client, len);

    close(s);

    return 0;
}