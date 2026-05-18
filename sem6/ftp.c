//client side :
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int s;
    struct sockaddr_in client;
    char filename[100], buffer[1024];

    s = socket(AF_INET, SOCK_STREAM, 0);

    client.sin_family = AF_INET;
    client.sin_port = htons(3000);
    client.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(s, (struct sockaddr*)&client, sizeof(client));

    printf("enter the name of file\n");
    scanf("%s", filename);

    send(s, filename, sizeof(filename), 0);

    printf("file contents from server:\n");

    while(recv(s, buffer,sizeof(buffer) , 0) > 0)
    {
        printf("%s", buffer);
    }

    close(s);

    return 0;
}


// server side:
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main()
{
    int s, ns;
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    char filename[100];
    char buffer[1024];

    s = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(3000);

    bind(s, (struct sockaddr*)&server, sizeof(server));

    listen(s, 5);

    ns = accept(s, (struct sockaddr*)&client, &len);

    recv(ns, filename, 100, 0);

    FILE *fp = fopen(filename, "r");

    if(fp == NULL)
    {
        send(ns, "File not found", 14, 0);
    }
    else
    {
        while(fgets(buffer, sizeof(buffer), fp))
        {
            send(ns, buffer, sizeof(buffer), 0);
        }
        fclose(fp);
    }

    close(ns);
    close(s);

    return 0;
}

{/*
while(fgets(buffer, 1024, fp))
{
    char *word = strtok(buffer, " ");

    while(word != NULL)
    {
        if(strlen(word) == 4)
        {
            count++;
        }
        word = strtok(NULL, " ");
    }
}
    */}