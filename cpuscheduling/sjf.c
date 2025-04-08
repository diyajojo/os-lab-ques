#include <stdio.h>

#define MAX 100

int n , at[MAX], bt[MAX], ct[MAX], tat[MAX], wt[MAX],done[MAX];
int time =0, completed=0,minindex=-1;
int minbust=1e9;

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
    printf("processno\t\t\tAT\t\t\tBT\t\t\tCT\t\t\tTAT\t\t\tWT\n");
    
    while(completed<n)
    {
        minxindex=-1;
        minbust=1e9;
        for (int i=0;i<n;i++)
        {
            if(at[i]<=time && done[i]==0 && bt[i]<minbust)
            {
                minbust=bt[i];
                minindex=i;
            }
        }
        
        if(minindex==-1)
        {
            time ++;
        }
        else
        {
            time+=bt[minindex];
            ct[minindex]=time;
            tat[minindex]=ct[minindex]-at[minindex];
            wt[minindex]=tat[minindex]-bt[minindex];
            
        
            done[minindex]=1;
            completed++;
            
            printf("P%d\t\t\t\t%d\t\t\t\t%d\t\t\t\t%d\t\t\t\t%d\t\t\t%d\n",(minindex+1),at[minindex],bt[minindex],ct[minindex],tat[minindex],wt[minindex]);
        }
    }
   
   return 0;
}