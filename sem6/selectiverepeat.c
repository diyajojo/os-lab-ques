// client side :

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int s;
    struct sockaddr_in client;
    struct timeval tv;

    int ack[20] = {0};

    s = socket(AF_INET, SOCK_STREAM, 0);

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = inet_addr("127.0.0.1");
    client.sin_port = htons(3000);

    connect(s, (struct sockaddr*)&client, sizeof(client));

    tv.tv_sec = 3;
    tv.tv_usec = 0;

    setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    int base = 1;
    int next;
    int window = 4;

    while (base <= 10)
    {
        next = base;

        // SEND WINDOW
        while (next < base + window && next <= 10)
        {
            if (ack[next] == 0)
            {
                send(s, &next, sizeof(next), 0);
                printf("Sent frame %d\n", next);
            }
            next++;
        }

        // RECEIVE ACKS
        for (int i = base; i < base + window && i <= 10; i++)
        {
            if (ack[i] == 0)
            {
                int response;
                recv(s, &response, sizeof(response), 0);

                if (response == i)
                {
                    ack[i] = 1;
                    printf("ACK received for %d\n", i);
                }
            }
        }

        // SLIDE WINDOW
        while (ack[base] == 1 && base <= 10)
            base++;
    }

    printf("All frames sent successfully\n");
    close(s);

    return 0;
}

// server side:
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int s, ns;
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    int frame;

    s = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(3000);

    bind(s, (struct sockaddr*)&server, sizeof(server));
    listen(s, 5);

    ns = accept(s, (struct sockaddr*)&client, &len);

    while (1)
    {
        recv(ns, &frame, sizeof(frame), 0);

        printf("Received frame %d\n", frame);

        send(ns, &frame, sizeof(frame), 0);

        printf("ACK sent for %d\n", frame);
    }

    close(ns);
    close(s);

    return 0;
}