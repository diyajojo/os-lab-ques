//client side:
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <string.h>

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

    for(int i=0;i<5;i++)
    {
        printf("enter packet to send\n");

        scanf("%s", packet);

        while(1)
        {
            send(s, packet, sizeof(packet), 0);

            printf("packet %d sent from client to server\n", i+1);

            int r = recv(s, ack, sizeof(ack), 0);

            if(r > 0)
            {
                printf("ack received for packet %d\n", i+1);

                break;
            }
            else
            {
                printf("ack not received for packet %d, retransmitting\n", i+1);
            }
        }
    }

    close(s);

    return 0;
}

//server side:
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

int main()
{
    int s, ns;

    struct sockaddr_in client, server;

    socklen_t len = sizeof(client);

    char packet[100];

    s = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(3000);

    bind(s, (struct sockaddr*)&server, sizeof(server));

    listen(s, 5);

    ns = accept(s, (struct sockaddr*)&client, &len);

    srand(time(0));

    while(1)
    {
        recv(ns, packet, sizeof(packet), 0);

        printf("packet arrived at server: %s\n", packet);

        if(rand() % 100 < 70)
        {
            send(ns, "ACK", 3, 0);

            printf("ack sent for received packet\n");
        }
        else
        {
            printf("ack not sent for arrived packet\n");
        }
    }

    close(ns);
    close(s);

    return 0;
}