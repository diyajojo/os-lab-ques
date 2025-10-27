#include <stdio.h>
#include <stdlib.h>

void main()
{
    int n;
    printf("enter the number of disk requests to be made\n");
    scanf("%d",&n);
    
    int track[n];
    printf("enter the track numbers of the disk to where requests are made\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&track[i]);
    }
    
    int currentTrack,nextTrack,totalSeektime;
    
    printf("enter the initial disk head\n");
    scanf("%d",&currentTrack);
    
    
    printf("%d->",currentTrack);
    
    for(int i=0;i<n;i++)
    {
        nextTrack=track[i];
        totalSeektime+=abs(currentTrack-nextTrack);
        printf("%d->",nextTrack);
        currentTrack=track[i];
    }
    printf("\n");
    printf("total seek time is %d \n",totalSeektime);
}