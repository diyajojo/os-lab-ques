#include <stdio.h>
#define MAX 1000

int n, at[MAX],bt[MAX],ct[MAX],tat[MAX],wt[MAX],pt[MAX],done[MAX];
int completed=0,time=0;
int priorityindex=-1;

int main()
{
     printf("enter the number of process\n");
    scanf("%d",&n);
    
    printf("enter the arrival time for each process\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&at[i]);
    }
    
    printf("enter the bust time for each process\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&bt[i]);
        done[i]=0;
    }
    
     printf("enter the priority for each process\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&pt[i]);
        done[i]=0;
    }
    
    printf("processno\t\t\tAT\t\t\tBT\t\t\tCT\t\t\tTAT\t\t\tWT\n");
    
    while(completed<n)
    {
        int minprio=1000;
        int priorityindex=-1;
        
        for(int i=0;i<n;i++)
        {
            if(at[i]<=time && done[i]==0 && pt[i]<minprio)
            {
                minprio=pt[i];
                priorityindex=i;
            }
        }
        if(priorityindex==-1)
        {
            time ++;    
        }
        else
        {
            time+=bt[priorityindex];
            ct[priorityindex]=time;
            tat[priorityindex]=ct[priorityindex]-at[priorityindex];
            wt[priorityindex]=tat[priorityindex]-bt[priorityindex];
            done[priorityindex]=1;
            completed++;
            
            printf("Priority%d\t\t\t\t%d\t\t\t\t%d\t\t\t\t%d\t\t\t\t%d\t\t\t%d\n",pt[priorityindex],at[priorityindex],bt[priorityindex],ct[priorityindex],tat[priorityindex],wt[priorityindex]);
        }
    }
    return 0;
}