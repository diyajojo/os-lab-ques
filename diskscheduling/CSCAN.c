#include <stdio.h>
#include <stdlib.h>

#define MAXREQ 10000
#define DISK_SIZE 200

int currentTrack=0, nextTrack=0, totalSeektime=0, temp=0,splitIndex=-1;

void CSCAN(int n,int request[],int head)
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
    
    if(splitIndex!=-1)
    {
        for(int i=splitIndex;i<n;i++)
        {
            nextTrack=request[i];
            totalSeektime+=abs(nextTrack-currentTrack);
            currentTrack=request[i];
        }
        
        totalSeektime+=abs(currentTrack-(DISK_SIZE-1));
        currentTrack=DISK_SIZE-1;
        
        currentTrack=0;
        
        for(int i=0;i<splitIndex;i++)
        {
            nextTrack=request[i];
            totalSeektime+=abs(nextTrack-currentTrack);
            currentTrack=request[i];
        }
    }
    
    printf("total seektime is %d\n",totalSeektime);
}


int main()
{
    int n,request[MAXREQ],head;
    
    printf("enter number of disk requests\n");
    scanf("%d",&n);
    
    printf("enter the track numbers of requested disks\n");
    for(int i=0;i<n;i++)
    {
    scanf("%d",&request[i]);
    }
    
    printf("enter the initial head disk\n");
    scanf("%d",&head);
    
    CSCAN(n,request,head);
    
    return 0;
}