#include <stdio.h>
#include <stdlib.h>

#define MAX 1000
#define DISK_SIZE 199

int n, trackno[MAX], currentTrack,nextTrack,totalSeektime;
int splitIndex=0;

int main()
{
    printf("enter the number of requests\n");
    scanf("%d",&n);
    
    printf("enter the track number of made requests\n");
    for(int i=0;i<n;i++)
    {
    scanf("%d",&trackno[i]);
    }
    
    printf("enter the initial disk head\n");
    scanf("%d",&currentTrack);
    
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(trackno[j]>trackno[j+1])
            {
                int temp=trackno[j];
                trackno[j]=trackno[j+1];
                trackno[j+1]=temp;
            }
        }
    }
    
    for(int i=0;i<n;i++)
    {
        if(trackno[i]>=currentTrack)
        {
            splitIndex=i;
            break;
        }
    }
    
    printf("%d->",currentTrack);
    
    for(int i=splitIndex;i<n;i++)
    {
        nextTrack=trackno[i];
        totalSeektime+=abs(nextTrack-currentTrack);
        currentTrack=trackno[i];
        printf("%d->",currentTrack);
    }
    
    if(currentTrack!=DISK_SIZE-1)
    {
        totalSeektime+=abs((DISK_SIZE -1)-currentTrack);
        currentTrack=DISK_SIZE -1;
        printf("%d->",currentTrack);
    }
    
    for(int i=splitIndex-1;i>=0;i--)
    {
        nextTrack=trackno[i];
        totalSeektime+=abs(currentTrack-nextTrack);
        currentTrack=trackno[i];
        printf("%d->",currentTrack);
    }
    
    printf("\ntotal seeektime is %d",totalSeektime);
    
    return 0;
}