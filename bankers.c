#include <stdio.h>

define MAX 100;

int p,r;
int max[MAX][MAX];
int alloc[MAX][MAX];
int avail[MAX];
int need[MAX][MAX];
int flag=0;
int count=0;

while (count<p)
{
    for(int i=0;i<p;i++)
    {
        
    }
}

int main()
{
    printf("enter the number of process and resources\n");
    scabf("%d%d",&p,&r);

    printf("enter the max resources matrix \n");
    for(int i=0;i<p;i++)
    {
        for (int j=0;j<r;j++)
        {
            scanf("%d",&max[i][j]);
        }
    }

    printf("enter the allocated resources matrix \n");
    for(int i=0;i<p;i++)
    {
        for (int j=0;j<r;j++)
        {
            scanf("%d",&alloc[i][j]);
        }
    }
    printf("enter the available resources \n");
    for(int i=0;i<r;i++)
    {
        scanf("%d",&avail[i]);
    }
    
    int k=ifisSafe(max,alloc,avail,p,r)
}