#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int n,src,des,cost[100][100],d[100],p[100],v[100],count=0,next;
    printf("enter number of nodes\n");
    scanf("%d",&n);
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
    
    for(int i=0;i<n;i++)
    {
        d[i]=cost[src][i];
        p[i]=src;
        v[i]=0;
    }
    d[src]=0;
    v[src]=1;
    count++;
    
    while(count < n-1)
    {
        int min=999;
        int next=-1;
        
        for(int i=0;i<n;i++)
        {
            if(v[i]==0 && d[i]<min)
            {
                min=d[i];
                next=i;
            }
        }
        if(next==-1)
        {
            break;
        }
        v[next]=1;
        
        for(int i=0;i<n;i++)
        {
            if(v[i]==0 && min+cost[next][i]<d[i])
            {
                d[i]=min+cost[next][i];
                p[i]=next;
            }
        }
        count++;
    }
    
    printf("node\tparent\tshortest distance");
    for(int i=0;i<n;i++)
    {
        printf("%d\t\t%d\t\t%d\n",i,p[i],d[i]);
    }
    printf("enter destination node\n");
    scanf("%d",&des);
    printf("path=%d",des);
    int j=des;
    while(j!=src)
    {
        j=p[j];
        printf("<--%d",j);
    }
    
    
    return 0;
}
