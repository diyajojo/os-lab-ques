#include <stdio.h>

#define MAX 1000

int max[MAX][MAX],alloc[MAX][MAX],avail[MAX],tempavail[MAX],finish[MAX],need[MAX][MAX];
int r,p, done =0 ,count =0,canRun=0;

int isSafe(int p,int r,int tempavail[],int finish[])
{
    while(count<p)
    {
        int done=0;
        for(int i=0;i<p;i++)
        {
            if (finish[i]==0)
            {
                canRun=1;
                for(int j=0;j<r;j++)
                {
                    need[i][j]=max[i][j]-alloc[i][j];
                    if(need[i][j]>tempavail[j])
                    {
                        canRun=0;
                        break;
                    }
                }
                if(canRun==1)
                {
                    for(int j=0;j<r;j++)
                    {
                        tempavail[j]+=alloc[i][j];
                    }
                     count++;
                     done++;
                     finish[i]=1;
                     printf("P%d->",(i+1));
                }
            }
        }
        if(done==0)
         return 0;
    }
    printf("\n");
    return 1;
}

int main()
{
    printf("enter the number of processes\n");
    scanf("%d",&p);
    
    printf("enter the number of resources\n");
    scanf("%d",&r);
    
    printf("enter the maximum resources\n");
    for(int i=0; i<p;i++)
    {
        for(int j=0;j<r;j++)
        {
            scanf("%d",&max[i][j]);
        }
    }
    
     printf("enter the allocated resources\n");
    for(int i=0; i<p;i++)
    {
        for(int j=0;j<r;j++)
        {
            scanf("%d",&alloc[i][j]);
        }
    }
    
    printf("enter the available resources\n");
    for(int i=0;i<r;i++)
    {
        scanf("%d",&avail[i]);
        tempavail[i]=avail[i];
    }
    
    for(int i=0;i<p;i++)
    {
        finish[i]=0;
    }
    
    int m=isSafe(p,r,tempavail,finish);
    if(m)
    {
        printf("no deadlock detected\n");
    }
    else
    {
        printf("deadlock detected\n");
    }
    
    return 0;
}