#include <stdio.h>
#include <stdlib.h>

#define MAX 100
int n, trackno[MAX],totalSeektime=0;
int nextTrack=0;
int currentTrack=0;

int main()
{
    printf("enter the number of disk reuqests\n");
    scanf("%d",&n);
    
    printf("enter the track number to where requests are made\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&trackno[i]);
    }
    
    printf("enter initial diskhead\n");
    scanf("%d",&currentTrack);
    
    printf("order of execution of track\n");
    printf("%d->",currentTrack);
    
    for(int i=0;i<n;i++)
    {
        nextTrack=trackno[i];
        totalSeektime+=abs(currentTrack-nextTrack);
        printf("%d->",nextTrack);
        currentTrack=trackno[i];
    }
    
    printf("\ntotal seek time is : %d",totalSeektime);
    
    return 0;
}