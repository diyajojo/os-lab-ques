#include <stdio.h>

#define MAX 100

int max[MAX][MAX],alloc[MAX][MAX],avail[MAX],tempavail[MAX],finish[MAX],need[MAX][MAX];
int r,p, done =0 ,count =0,canRun=0;


void isSafe(int p,int r,int tempavail[],int finish[])
{
    while(count <p)
    {
        done=0;
        for(int i=0;i<p;i++)
        {
            if(finish[i]==0)
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
                    
                    finish[i]=1;
                    count++;
                    done++;
                }
            }
        }
        
        if(done==0)
        {
            printf("deadlock detected\n");
        }
        else
        {
            printf("deadlock not detected\n");
        }
    }
}

int main()
{
    printf("enter the number of process and resources\n");
    scanf("%d%d",&p,&r);
    
    printf("enter the maximum resources matrix\n");
    for(int i=0;i<p;i++)
    {
        for(int j=0;j<r;j++)
        {
            scanf("%d",&max[i][j]);
        }
    }
    
    printf("enter the allocated resource matrix\n");
    for(int i=0;i<p;i++)
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
    
    isSafe (p,r,tempavail,finish);
    return 0;
}