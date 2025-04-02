#include <stdio.h>

#define FRAME_SIZE 3

int frames[FRAME_SIZE];
int found=0;
int rear=-1;
int page_fault=0;

void initialize()
{
    for(int i=0;i<FRAME_SIZE;i++)
    {
        frames[i]=-1;
    }
}

void displayFrames()
{
    for(int i=0;i<FRAME_SIZE;i++)
    {
        if(frames[i]==-1)
        {
            printf("%d\t",-1);
        }
        else
        {
            printf("%d\t",frames[i]);
        }
    }
    printf("\n");
}

void fifo(int n,int pages[])
{
   for(int i=0;i<n;i++)
   {
    int page=pages[i];
    found=0;

    for(int j=0;j<FRAME_SIZE;j++)
    {
       if(frames[j]==page) 
       {
           found=1;
           break;
       }
    }
    if(found==0)
    {
        rear=(rear+1)%FRAME_SIZE;
        frames[rear]=page;
        page_fault++;
    }
    displayFrames();
   }
}

int main()
{
    int n,pages[20];

    printf("enter the number of pages\n");
    scanf("%d",&n);

    printf("enter the page sequence\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&pages[i]);
    }

    initialize();
    fifo(n,pages);


    return 0;
}