#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int max[MAX][MAX],alloc[MAX][MAX],avail[MAX],tempavail[MAX],finish[MAX],need[MAX][MAX];
int r,p,count =0,canRun=0;

void isSafe()
{
    while(count<p)
    {
        int done=0;
        for(int i=0;i<p;i++)
        {
            if(finish[i]==0)
            {
                canRun=1;
                for(int j=0;j<r;j++)
                {
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
                        tempavail[j]+=need[i][j];
                    }
                    done=1;
                    count++;
                    finish[i]=1;
                    printf("P%d->",(i+1));
                }
            }
        }
        if(done==0)
        {
            printf("\n deadlock detected\n");
        }
    }
    printf("\n no deadlock detected");
}




int main()
{
    printf("enter the number of processs\n");
    scanf("%d",&p);
    
    printf("enter the number of resources\n");
    scanf("%d",&r);
    
    printf("enter the maximum resources for each process\n");
    for(int i=0;i<p;i++)
    {
        for(int j=0;i<r;j++)
        {
            scanf("%d",&max[i][j]);
        }
    }
    
    printf("enter the allocated resources for each process\n");
    for(int i=0;i<p;i++)
    {
        for(int j=0;i<r;j++)
        {
            scanf("%d",&alloc[i][j]);
        }
    }
    
    for(int i=0;i<p;i++)
    {
        for(int j=0;i<r;j++)
        {
            need[i][j]=max[i][j]=alloc[i][j];
        }
    }
    
    printf("enter the available resource of each type\n");
    for(int i=0;i<r;i++)
    {
        scanf("%d",&avail[i]);
        tempavail[i]=avail[i];
    }
    for(int i=0;i<p;i++)
    {
      finish[i]=0;
    }
    
    isSafe();
    
}