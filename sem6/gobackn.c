// client side :
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/time.h>

int main()
{
    int s;

    struct sockaddr_in client;

    struct timeval tv;

    char packet[100], ack[100];

    s = socket(AF_INET, SOCK_STREAM, 0);

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = inet_addr("127.0.0.1");
    client.sin_port = htons(3000);

    connect(s, (struct sockaddr*)&client, sizeof(client));

    tv.tv_sec = 3;
    tv.tv_usec = 0;

    setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    int base = 1;
    int next = 1;
    int window = 4;

    while(base <= 5)
    {
        // send packets inside window
        while(next < base + window && next <= 5)
        {
            printf("enter packet %d: ", next);

            scanf("%s", packet);

            send(s, packet, sizeof(packet), 0);

            printf("packet %d sent\n", next);

            next++;
        }

        int r = recv(s, ack, sizeof(ack), 0);

        if(r > 0)
        {
            printf("ACK received for %s\n\n", ack);

            base++;
        }
        else
        {
            printf("timeout\n");

            printf("retransmitting from packet %d\n\n", base);

            next = base;
        }
    }

    printf("all packets sent successfully\n");

    close(s);

    return 0;
}


// server side:
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

int main()
{
    int s, ns;

    struct sockaddr_in server, client;

    socklen_t len = sizeof(client);

    char packet[100];

    s = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(3000);

    bind(s, (struct sockaddr*)&server, sizeof(server));

    listen(s, 5);

    ns = accept(s, (struct sockaddr*)&client, &len);

    while(1)
    {
        recv(ns, packet, sizeof(packet), 0);

        printf("packet received: %s\n", packet);

        // randomly lose ACK
        if(rand() % 2)
        {
            send(ns, packet, sizeof(packet), 0);

            printf("ACK sent for %s\n\n", packet);
        }
        else
        {
            printf("ACK lost for %s\n\n", packet);
        }
    }

    close(ns);
    close(s);

    return 0;
}