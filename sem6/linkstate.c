#include <stdio.h>

int main()
{
    int n,count=0,src,dest,next;
    printf("enter the number of nodes\n");
    scanf("%d",&n);
    
    int cost[n][n],dist[n],parent[n],visited[n];
    printf("enter the cost matrix\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            scanf("%d",&cost[i][j]);
            
            if(cost[i][j]==0)
            {
                cost[i][j]=999;
            }
        }
    }
    
    printf("enter the source node\n");
    scanf("%d",&src);
    printf("enter the destination node\n");
    scanf("%d",&dest);
    
    for(int i=0;i<n;i++)
    {
        dist[i]=cost[src][i];
        visited[i]=0;
        parent[i]=src;
    }
    dist[src]=0;
    visited[src]=1;
    count++;
    
    while(count<n-1)
    {
        int min=999;
        for(int i=0;i<n;i++)
        {
            if(visited[i]==0 && dist[i]<min)
            {
                min=dist[i];
                next=i;
            }
        }
        
        visited[next]=1;
        
        for(int i=0;i<n;i++)
        {
            if(visited[i]==0 && min+cost[next][i]<dist[i])
            {
                dist[i]=min+cost[next][i];
                parent[i]=next;
            }
        }
        count++;
    }
    
    printf("shortest distance from source node to other nodes are:\n");
    printf("node\t\tdistance\t\tparent node\n");
    for(int i=0;i<n;i++)
    {
        printf("%d\t\t\t\t%d\t\t\t\t%d\n",i,dist[i],parent[i]);
    }
    printf("path from source to destination node is:\n");
    printf("path=%d",dest);
    
    int j=dest;
    while(j!=src)
    {
        j=parent[j];
        printf("<--%d",j);
    }
    
}