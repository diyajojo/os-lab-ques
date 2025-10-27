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

int findLRU()
{
    int max=counter[0];
    int lruIndex=0;
    
    for(int j=1;j<FRAME;j++)
    {
        if(counter[j]>max)
        {
            max=counter[j];
            lruIndex=j;
        }
    }
    return lruIndex;
}

void LRU(int n,int pages[])
{
    for(int i=0;i<n;i++)
    {
        int page=pages[i];
        int flag=0;
        for(int j=0;j<FRAME;j++)
        {
            if(frames[j]==page)
            {
                pagehit++;
                flag=1;
                break;
            }
        }
        if(flag==0)
        {
            int lruIndex=findLRU();
            frames[lruIndex]=page;
            counter[lruIndex]=0;
            pagefault++;
            
        }
        
        for(int i=0;i<FRAME;i++)
        {
            counter[i]++;
        }
        
        for(int i=0;i<FRAME;i++)
        {
            if(frames[i]==page)
            {
                counter[i]=0;
                break;
            }
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
        frames[i]=-1;
        counter[i]=0;
    }
    
    LRU(n,pages);
    
    printf("page hit is %d\n",pagehit);
    printf("page fault is %d\n",pagefault);
}