// client code:
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int s, n;
    int fib[100];
    struct sockaddr_in client;

    s = socket(AF_INET, SOCK_STREAM, 0);

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = inet_addr("127.0.0.1");
    client.sin_port = htons(3000);

    connect(s, (struct sockaddr*)&client, sizeof(client));

    printf("Enter number of terms: ");
    scanf("%d", &n);

    send(s, &n, sizeof(n), 0);

    recv(s, fib, sizeof(int) * n, 0);

    printf("Fibonacci series:\n");

    for(int i = 0; i < n; i++)
    {
        printf("%d ", fib[i]);
    }

    printf("\n");

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
    int s, ns, n;
    int fib[100];
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    s = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(3000);

    bind(s, (struct sockaddr*)&server, sizeof(server));
    listen(s, 5);

    ns = accept(s, (struct sockaddr*)&client, &len);

    recv(ns, &n, sizeof(n), 0);

    fib[0] = 0;
    fib[1] = 1;

    for(int i = 2; i < n; i++)
    {
        fib[i] = fib[i-1] + fib[i-2];
    }

    send(ns, fib, sizeof(int) * n, 0);

    close(ns);
    close(s);

    return 0;
}