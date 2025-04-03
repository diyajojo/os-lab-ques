#include <stdio.h>
#include <stdlib.h>

#define MAXREQ 1000

int currentTrack=0, nextTrack=0, totalSeektime=0, temp=0,splitIndex=-1;

void SCAN(int n,int request[],int head)
{
    currentTrack=head;
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(request[j]>request[j+1])
            {
                temp=request[j];
                request[j]=request[j+1];
                request[j+1]=temp;
            }
        }
    }
    for(int i=0;i<n;i++)
    {
        if(request[i]>=head)
        {
            splitIndex=i;
            break;
        }
    }
    
    for(int i=splitIndex;i<n;i++)
    {
        nextTrack=request[i];
        totalSeektime+=abs(nextTrack-currentTrack);
        currentTrack=request[i];
    }
    
    for(int i=0;i<splitIndex;i++)
    {
        nextTrack=request[i];
        totalSeektime+=abs(nextTrack-currentTrack);
        currentTrack=request[i];
        
    }
    
    printf("total seek time is %d\n",totalSeektime);
    
}

int main()
{
    int n,request[MAXREQ],head;
    
    printf("enter the number of disk requests\n");
    scanf("%d",&n);
    
    printf("enter the track numbers of the resp disk requests\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&request[i]);
    }
    
    printf("enter the number of initial disk head\n");
    scanf("%d",&head);
    
    SCAN(n,request,head);
    
    return 0;
}