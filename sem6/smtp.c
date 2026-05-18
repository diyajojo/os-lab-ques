//server code :
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

int main()
{
    int s,ns;

    struct sockaddr_in client,server;

    socklen_t len=sizeof(client);

    char buffer[1024];

    s=socket(AF_INET,SOCK_STREAM,0);

    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(3000);

    bind(s,(struct sockaddr*)&server,sizeof(server));

    listen(s,5);

    ns=accept(s,(struct sockaddr*)&client,&len);

    while(1)
    {
        recv(ns,buffer,sizeof(buffer),0);

        if(strncmp(buffer,"to",2)==0)
        {
            printf("%s",buffer);
        }

        else if(strncmp(buffer,"from",4)==0)
        {
            printf("%s",buffer);
        }

        else if(strncmp(buffer,"email-body-header",17)==0)
        {
            printf("%s\n",buffer);

            while(1)
            {
                recv(ns,buffer,sizeof(buffer),0);

                if(strcmp(buffer,".\n")==0)
                {
                    break;
                }

                printf("%s",buffer);
            }
        }

        else if(strncmp(buffer,"quit",4)==0)
        {
            printf("closing email transfer\n");

            break;
        }
    }

    close(ns);
    close(s);

    return 0;
}

// client code :
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

int main()
{
    int s;

    struct sockaddr_in client;

    char buffer[100],msg[1024];

    s = socket(AF_INET, SOCK_STREAM, 0);

    client.sin_family = AF_INET;
    client.sin_port = htons(3000);
    client.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(s, (struct sockaddr*)&client, sizeof(client));

    printf("enter the to mail:\n");
    fgets(buffer,100,stdin);

    send(s,buffer,sizeof(buffer),0);

    printf("to mail sent to server\n");

    printf("enter the from mail:\n");
    fgets(buffer,100,stdin);

    send(s,buffer,sizeof(buffer),0);

    printf("from mail sent to server\n");

    send(s,"email-body-header",17,0);

    printf("email-body-header sent to server\n");

    printf("enter the email to be send (end with .)\n");

    while(1)
    {
        fgets(msg,1024,stdin);

        send(s,msg,sizeof(msg),0);

        if(strcmp(msg,".\n")==0)
        {
            break;
        }
    }

    printf("email-body sent to server\n");

    send(s,"quit",4,0);

    printf("signal to stop emailing sent to server\n");

    close(s);

    return 0;
}