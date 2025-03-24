{/** */ we sort the process based on at and then calculate the wt and tat and then avg wt and tat */}

#include <stdio.h>

#define MAX 10

int np,at[MAX],bt[MAX],wt[MAX],tat[MAX],avgwt,avgtat,sumWT,sumTAT,t1,t2;

void sortArrivalTime(int np,int at[],int bt[])
{
    for(int i=0;i<np-1;i++)
    {
        for(int j=0;j<np-1-i;j++)
        {
            if(at[j]>at[j+1])
            {
                t1=at[j];
                at[j]=at[j+1];
                at[j+1]=t1;
                
                t2=bt[j];
                bt[j]=bt[j+1];
                bt[j+1]=t2;
            }
        }
    }
}

void  findWT(int np,int at[],int bt[])
{
    wt[0]=0;
    for(int i=1;i<np;i++)
    {
        wt[i]=at[i+1]+bt[i+1]+wt[i+1]-at[i];
    }
}
void  findTAT(int np,int bt[],int wt[])
{
    for(int i=0;i<np;i++)
    {
        tat[i]=wt[i]+bt[i];
    }
}

void avgTime(int np,int at[],int bt[])
{
    findWT(np,at,bt);
    findTAT(np,bt,wt);
    
    for(int i=0;i<np;i++)
    {
         sumWT+=wt[i];
         sumTAT+=tat[i];
    }
    avgwt=sumWT/np;
    avgtat=sumTAT/np;
    printf("avg tat and avg wt is:\t%d and %d",avgtat,avgwt);
}




int main()
{
    int np=5;
    int at[]={23,45,63,12,33};
    int bt[]={2,4,6,8,10};

    sortArrivalTime(np,at,bt);
    avgTime(np,bt,at);
    

    return 0;
}