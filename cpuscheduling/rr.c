//The execution of a process can be interrupted (or paused) before it finishes, allowing another process to run.

#include <stdio.h>

int main()
{
    int n,at[1000],bt[1000],wt[1000],tat[1000],ct[1000],rt[1000],time=0;
    int completed=0;
    int quantam=2;
    
    printf("enter the number of processes\n");
    scanf("%d",&n);
    
    printf("enter the arrival for each process\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&at[i]);
    }
    
    printf("enter the burst time for each process\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&bt[i]);
        rt[i]=bt[i];
    }
      printf("process no\t\tarrivaltime\t\tbursttime\t\twaitingtime\t\tturnaroundtime\n");
      
    while(completed<n)
    {
    int flag = 1;
    
        for(int i=0;i<n;i++)
        {
            if(at[i]<=time && rt[i]>0)
            {
                flag=0;
                if(rt[i]<=quantam)
                {
                    time+=rt[i];
                    rt[i]=0;
                    ct[i]=time;
                    completed++;
                    
                    tat[i]=ct[i]-at[i];
                    wt[i]=tat[i]-bt[i];
                    
                    printf("P%d\t\t\t\t%d\t\t\t\t%d\t\t\t\t%d\t\t\t\t%d\n",(i+1),at[i],bt[i],wt[i],tat[i]);
                    
                }
                else
                {
                time+=quantam;
                rt[i]-=quantam;
                }
            }
        }
        if(flag==1)
        {
            time++;
        }
    }
    return 0;
}