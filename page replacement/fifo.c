#include <stdio.h>

#define FRAME_SIZE 3;

int frames[FRAME_SIZE];
int found=0;

void initialize()
{
    for(int i=0;i<FRAME_SIZE;i++)
    {
        frames[i]=-1;
    }
}

void fifo(int n,int pages[])
{
   for(int i=0;i<n;i++)
   {
    int page=pages[i];
    found=0;

    for(int i=0;i<FRAME_SIZE;i++)
    {
        
    }
   }
}

int main()
{
    int n,pages[20];

    printf("enter the number of pages\n");
    scanf("%d",&n)

    printf("enter the page sequence");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&pages[i]);
    }

    initialize();
    fifo(n,pages)


    return 0;
}