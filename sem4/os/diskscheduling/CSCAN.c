#include <stdio.h>
#include <stdlib.h>

#define DISK_SIZE 199   
#define MAX 1000

int n,trackno[MAX],nextTrack,currentTrack,splitindex,totalSeektime;

int main()
{
    printf("enter the number of requests\n");
    scanf("%d",&n);
    
    printf("enter the track number to which request was made\n");
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
                int temp = trackno[j];
                trackno[j]=trackno[j+1];
                trackno[j+1]=temp;
            }
        }
    }
    
    for(int i=0;i<n;i++)
    {
        if(trackno[i]>=currentTrack)
        {
            splitindex=i;
            break;
        }
    }
    
    printf("%d->",currentTrack);
    
    for(int i=splitindex;i<n;i++)
    {
        nextTrack=trackno[i];
        totalSeektime+=abs(nextTrack-currentTrack);
        currentTrack=trackno[i];
        printf("%d->",currentTrack);
    }
    
    if(currentTrack!=DISK_SIZE-1)
    {
        totalSeektime+=abs(currentTrack-(DISK_SIZE -1));
        currentTrack=DISK_SIZE -1;
        printf("%d->",currentTrack);
    }
    
    totalSeektime+=abs(DISK_SIZE -1);
    currentTrack=0;
    printf("%d->",currentTrack);
    
    for(int i=0;i<splitindex;i++)
    {
        nextTrack=trackno[i];
        totalSeektime+=abs(currentTrack-nextTrack);
        currentTrack=trackno[i];
        printf("%d->",currentTrack);
    }
    
    printf("\n total seektime is:",totalSeektime);
    return 0;
}