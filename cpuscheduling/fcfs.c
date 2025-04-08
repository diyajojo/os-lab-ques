#include <stdio.h>

#define SIZE 100

int at[SIZE],bt[SIZE],ct[SIZE],tat[SIZE],wt[SIZE];

int main()
{
    int np;
    printf("enter the number of process\n");
    scanf("%d",&np);
    
    printf("enter the arrival time for each process\n");
    for(int i=0;i<np;i++)
    {
        scanf("%d",&at[i]);
    }
    
    printf("enter the burst time for each process\n");
    for(int i=0;i<np;i++)
    {
        scanf("%d",&bt[i]);
    }
    
    for(int i=0;i<np-1;i++)
    {
        for(int j=0;j<np-i-1;j++)
        {
            if(at[j]>at[j+1])
            {
                int temp1=at[j];
                at[j]=at[j+1];
                at[j+1]=temp1;
                
                int temp2=bt[j];
                bt[j]=bt[j+1];
                bt[j+1]=temp2;
            }
        }
    }
    
    
    ct[0]=at[0]+bt[0];
    tat[0]=ct[0]-at[0];
    wt[0]=tat[0]-bt[0]
    for(int i=1;i<np;i++)
    {
        if(at[i]>ct[i-1])
        {
            ct[i]=at[i]+bt[i];
        }
        else
        {
            ct[i]=ct[i-1]+bt[i];
        }
        
        tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i];
    }
    
    printf("PNO\t\tAT\t\t\tBT\t\t\tCT\t\t\tTAT\t\t\tWT\n");
    
    for(int i=0;i<np;i++)
    {
        printf("%d\t\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\n",(i+1),at[i],bt[i],ct[i],tat[i],wt[i]);
    }
    
     return 0;
}