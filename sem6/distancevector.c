#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    struct router
    {
        int cost[10];
        int from[10];
    } rtr[10];
    
    int n,cost[100][100];
    printf("enter number of routers\n");
    scanf("%d",&n);
    
    printf("enter the cost matrix\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            scanf("%d",&cost[i][j]);
            
            rtr[i].cost[j]=cost[i][j];
            rtr[i].from[j]=j;
        }
    }
    
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            for(int k=0;k<n;k++)
            {
                if(rtr[i].cost[j]>cost[i][k]+rtr[k].cost[j])
                {
                    rtr[i].cost[j]=cost[i][k]+rtr[k].cost[j];
                    rtr[i].from[j]=k;
                }
            }
        }
    }
    for(int i=0;i<n;i++)
    {
        printf("routing table for %d:\n",i+1);
        
        for(int j=0;j<n;j++)
        {
            printf("%d->%d=%d\n",j+1,rtr[i].from[j]+1,rtr[i].cost[j]);
        }
    }
    
    
    
    
    return 0;
}