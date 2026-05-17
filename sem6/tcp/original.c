
// client side:

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int s;
    struct sockaddr_in client;
    char buffer[100];

    s = socket(AF_INET, SOCK_STREAM, 0);

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = inet_addr("127.0.0.1");
    client.sin_port = htons(3000);

    connect(s, (struct sockaddr*)&client, sizeof(client));

    printf("enter message to send to server\n");
    fgets(buffer, 100, stdin);

    send(s, buffer, 100, 0);

    recv(s, buffer, 100, 0);

    printf("message from server is: %s\n", buffer);

    close(s);

    return 0;
}


// server side:

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int s, newsock;
    struct sockaddr_in server, client;
    char buffer[100];
    socklen_t len = sizeof(client);

    s = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(3000);

    bind(s, (struct sockaddr*)&server, sizeof(server));

    listen(s, 5);

    newsock = accept(s, (struct sockaddr*)&client, &len);

    recv(newsock, buffer, 100, 0);
    printf("message from client is: %s\n", buffer);

    printf("enter message to send to client\n");
    fgets(buffer, 100, stdin);

    send(newsock, buffer, 100, 0);

    close(newsock);
    close(s);

    return 0;
}


