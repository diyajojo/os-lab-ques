#include <stdio.h>

#define FRAME 3

int frames[FRAME] ,rear=-1 ;
int pagefault=0,pagehit=0;

void displayFrames()
{
    for(int i=0;i<FRAME;i++)
    {
        if(frames[i]==-1)
        {
            printf("%d\t\t\t",-1);
        }
        else
        {
            printf("%d\t\t\t\t",frames[i]);
        }
    }
    printf("\n");
}

void fifo(int n,int pages[])
{
    for(int i=0;i<n;i++)
    {
        int page=pages[i];
        int found=0;
        
        for(int j=0;j<FRAME;j++)
        {
            if(page==frames[j])
            {
                pagehit++;
                found=1;
                break;
            }
        }
        
        if(found==0)
        {
            rear=(rear+1)%FRAME;
            pagefault++;
            frames[rear]=page;
        }
        displayFrames();
    }
}


int main()
{
    int n;
    
    printf("enter the number of pages\n");
    scanf("%d",&n);
    
    int pages[n];
    printf("enter the page sequence to be loaded into memory\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&pages[i]);
    }
    
    for(int i=0;i<FRAME;i++)
    {
        frames[i]=-1;
    }
    
    fifo(n,pages);

    printf("page fault is :%d\n",pagefault);
    printf("page hit is :%d\n",pagehit);
    
    return 0;
}

