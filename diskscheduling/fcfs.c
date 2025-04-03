#include <stdio.h>
#include <stdlib.h>


#define MAXREQ 100

int currentTrack=0;
int nextTrack=0;
int totalSeektime=0;

void fcfs(int n,int request[])
{
    for(int i=0;i<n;i++)
    {
        nextTrack=request[i];
        totalSeektime+=abs(nextTrack-currentTrack);
        currentTrack=request[i];
    }
    
    printf("total seektime is %d\n",totalSeektime);
}


int main()
{
    int n,request [MAXREQ];
    
    printf("enter the number of disk request\n");
    scanf("%d",&n);
    
    printf("enter the rack number of resp disk requests\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&request[i]);
    }
    
    fcfs(n,request);
    
    return 0;
}
