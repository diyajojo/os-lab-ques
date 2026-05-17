// client code:
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main()
{
    int s,num;
    struct sockaddr_in client;
    
    s=socket(AF_INET,SOCK_STREAM,0);
    
    client.sin_family=AF_INET;
    client.sin_addr.s_addr=inet_addr("127.0.0.1");
    client.sin_port=htons(3000);
    
    connect(s,(struct sockaddr*)&client,sizeof(client));
    
    printf("enter number to check primality\n");
    scanf("%d",&num);
    
    send(s,&num,sizeof(num),0);
    recv(s,&num,sizeof(num),0);
    
    if(num==1)
    {
        printf("number is prime\n");
    }
    else
    {
        printf("number not prime\n");
    }
    
    close(s);
    
    
    return 0;
}





// server side :
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int s, ns, num, count = 0, flag = 0;
    struct sockaddr_in client, server;
    socklen_t len = sizeof(client);

    s = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(3000);

    bind(s, (struct sockaddr*)&server, sizeof(server));

    listen(s, 5);

    ns = accept(s, (struct sockaddr*)&client, &len);

    recv(ns, &num, sizeof(num), 0);

    for(int i = 1; i <= num; i++)
    {
        if((num % i) == 0)
        {
            count++;
        }
    }

    if(count == 2)
        flag = 1;
    else
        flag = 0;

    send(ns, &flag, sizeof(flag), 0);

    close(ns);
    close(s);

    return 0;
}