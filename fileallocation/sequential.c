#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct File
{
    char name[20];
    int start;
    int end;
};

#define MAX_BLOCK 50
#define MAX_FILE 50


int disk[MAX_BLOCK];
struct File files[MAX_FILE];
int choice;
int fileCount=0;
int totalBlocks=0;

void initializeBlocks(int totalBlocks)
{
    for(int i=0;i<totalBlocks;i++)
    {
        disk[i]=0;
    }
}

void allocateFile()
{
    char fname[20];
    int size, start=-1,count=0;
    
    printf("enter file name\n");
    scanf("%s",fname);
    
    printf("enter file size\n");
    scanf("%d",&size);
    
    for (int i=0;i<totalBlocks;i++)
    {
        if (disk[i]==0)
        {
           if (start == -1)
           {
               start=i;
           }
           count++;
           if(count==size)
           {
               for(int j=start;j<start+size;j++)
               {
                   disk[j]=1;
               }
               strcpy(files[fileCount].name,fname);
               files[fileCount].start=start;
               files[fileCount].end=start+size-1;
               fileCount++;
               return;
           }
        }
        else
        {
            start=-1;
            count=0;
        }
    }
    
    printf("not enough continous space avaialable\n");
}

void viewFile()
{
    if (fileCount==0)
    {
        printf("no files are allocated\n");
    }
    for(int i=0;i<fileCount;i++)
    {
        printf("file %s have been allocated from block %d to block %d\n",files[i].name,files[i].start,files[i].end);
    }
}
void viewBlock()
{
    for(int i=0;i<totalBlocks;i++)
    {
        if(disk[i]==0)
        {
            printf("disk %d is free\n",i);
        }
        else
        {
           printf("disk %d is not free\n",i);
        }
    }
}
int main()
{
    printf("enter total number of blocks\n");
    scanf("%d",&totalBlocks);
    
    initializeBlocks(totalBlocks);
    
    while (1)
    {
    printf("enter 1 for file allocation\n");
    printf("enter 2 for viewing files\n");
    printf("enter 3 for viewing diskblocks\n");
    printf("enter 4 to exit\n");
    
    printf("enter choice\n");
    scanf("%d",&choice);
    
    if (choice==1)
    {
        allocateFile();
    }
    if (choice==2)
    {
        viewFile();
    }
    if (choice==3)
    {
        viewBlock();
    }
    if (choice==4)
    {
        exit(0);
    }
    
    }
    return 0;
}