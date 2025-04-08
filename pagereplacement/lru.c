#include <stdio.h>

#define MAX_FRAMES 3

int frames[MAX_FRAMES],counter[MAX_FRAMES];
int found=0;
int page_faults;

void initialize()
{
    for(int i=0;i<MAX_FRAMES;i++)
    {
        frames[i]=-1;
        counter[i]=0;
    }
}

int findLRU()
{
    int lru=0;
    for(int i=1;i<MAX_FRAMES;i++)
    {
        if(counter[i]>counter[lru])
        {
            lru=i;
        }
    }
    return lru;
}

void displayFrames()
{
    for(int i=0;i<MAX_FRAMES;i++)
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

void LRU(int n,int pages[])
{
    for(int i=0;i<n;i++)
    {
        int page=pages[i];
        found=0;
        for(int j=0;j<MAX_FRAMES;j++)
        {
            if(frames[j]==page)
            {
                found=1;
                break;
            }
        }
        if(found==0)
        {
            int lru=findLRU();
            frames[lru]=page;
            counter[lru]=0;
            page_faults++;
        }
        for(int i=0;i<MAX_FRAMES;i++)
        {
            counter[i]++;
        }
        for(int i=0;i<MAX_FRAMES;i++)
        {
            if(pages[i]==page)
            {
                counter[i]=0;
            }
        }
        
        displayFrames();
    }
}


int main()
{
    int n,pages[10];
    
    printf("enter the number of pages\n");
    scanf("%d",&n);
    
    printf("enter the page sequence\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&pages[i]);
    }
    
    initialize();
    LRU(n,pages);

    return 0;
    
}


#include <stdio.h>
#include <stdbool.h>

#define P 5  
#define R 3 

bool isSafe(int avail[], int max[][R], int allot[][R]) 
{
    int work[R];
    bool finish[P] = {0};
    int safeSeq[P];
    int count = 0;
    
    for (int i = 0; i < R; i++) 
        work[i] = avail[i];
    
    int need[P][R];
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = max[i][j] - allot[i][j];
    
    bool found;
    do 
    {
        found = false;
        for (int p = 0; p < P; p++) 
        {
            if (finish[p]) 
                continue;
            bool canAllocate = true;
            for (int j = 0; j < R; j++) 
            {
                if (need[p][j] > work[j]) 
                {
                    canAllocate = false;
                    break;
                }
            }
            if (canAllocate) 
            {
                for (int j = 0; j < R; j++) 
                    work[j] += allot[p][j];
                
                safeSeq[count++] = p;
                finish[p] = true;
                found = true;
            }
        }
    }
     while (found && count < P);
    if (count < P) {
        return false;
    }
    printf("Safe sequence: ");
    for (int i = 0; i < P; i++)
        printf("%d ", safeSeq[i]);
    printf("\n");
    return true;
}
bool requestResources(int processID, int request[], int avail[], int max[][R], int allot[][R]) 
{
    int need[P][R];
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = max[i][j] - allot[i][j];
    for (int i = 0; i < R; i++) 
    {
        if (request[i] > need[processID][i]) 
        {
            printf("Error: Process %d has exceeded its remaining need.\n", processID);
            printf("Request: %d, Need: %d for resource %d\n", 
                   request[i], need[processID][i], i);
            return false;
        }
    }
    for (int i = 0; i < R; i++) 
    {
        if (request[i] > avail[i]) 
        {
            printf("Error: Resources not available for Process %d.\n", processID);
            return false;
        }
    }
    for (int i = 0; i < R; i++) 
    {
        avail[i] -= request[i];
        allot[processID][i] += request[i];
    }
    if (isSafe(avail, max, allot)) 
    {
        printf("Request granted for Process %d.\n", processID);
        return true;
    } 
    else 
    {
        printf("Request denied for Process %d. System would be in an unsafe state.\n", processID);
        for (int i = 0; i < R; i++) 
        {
            avail[i] += request[i];
            allot[processID][i] -= request[i];
        }
        return false;
    }
}

void displayState(int avail[], int max[][R], int allot[][R]) 
{
    int need[P][R];
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = max[i][j] - allot[i][j];
    printf("\nCurrent System State:\n");
    printf("Process\tAllocation\tMax\tNeed\tAvailable\n");
    for (int i = 0; i < P; i++) 
    {
        printf("P%d\t", i);
        for (int j = 0; j < R; j++)
            printf("%d ", allot[i][j]);
        printf("\t\t");
        for (int j = 0; j < R; j++)
            printf("%d ", max[i][j]);
        printf("\t");
        for (int j = 0; j < R; j++)
            printf("%d ", need[i][j]);
        if (i == 0) 
        {
            printf("\t");
            for (int j = 0; j < R; j++)
                printf("%d ", avail[j]);
        }
        
        printf("\n");
    }
    printf("\n");
}

