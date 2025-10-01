#include <stdio.h>

#define FRAME 3

int frames[FRAME],counter[FRAME],n;
int pagefault=0,pagehit=0;

void displayFrames()
{
    for(int j=0;j<FRAME;j++)
    {
        if (frames[j]==-1)
        {
            printf("-1\t\t\t");
        }
        else
        {
            printf("%d\t\t\t",frames[j]);
        }
    }
    printf("\n");
}


int findlfu()
{
    int min=counter[0];
    int lfuIndex=0;
    
    for(int i=0;i<FRAME;i++)
    {
        if(counter[i]<min)
        {
            min=counter[i];
            lfuIndex=i;
        }
    }
    
    return lfuIndex;
}

void lfu(int n,int pages[])
{
    for(int i=0;i<n;i++)
    {
        int found=0;
        int page=pages[i];
        
        for(int j=0;j<FRAME;j++)
        {
            if(frames[j]==page)
            {
                counter[j]++;
                pagehit++;
                found=1;
                break;
            }
        }
        
        if(found==0)
        {
            int lfuIndex=findlfu();
            frames[lfuIndex]=page;
            counter[lfuIndex]=1;
            pagefault++;
        }
        
        displayFrames();
    }
}

int main()
{
    printf("enter the number of pages\n");
    scanf("%d",&n);
    
    int pages[n];
    printf("enter the page sequence\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&pages[i]);
    }
    
    for(int i=0;i<FRAME;i++)
    {
        counter[i]=0;
        frames[i]=-1;
    }
    
    
    lfu(n,pages);
    
   printf("page hit is %d\n",pagehit);
   printf("page fault is %d\n",pagefault);
}