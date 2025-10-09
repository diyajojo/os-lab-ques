#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BLOCKS 50
#define MAX_FILES 50

struct File
{
    char name[20];
    int indexBlock;
    int dataBlocks[MAX_BLOCKS];
    int size;
};

int disk[MAX_BLOCKS];
int data[MAX_BLOCKS];
struct File file[MAX_FILES];
int totalBlocks;
int totalFiles=0;
int choice;

void initializeBlocks(int totalBlocks)
{
    for(int i=0;i<totalBlocks;i++)
    {
        disk[i]=0;
    }
}

void allocateFiles()
{
    int indexBlock=-1;
    int size;
    char fname[20];
    
    printf("enter filename:\n");
    scanf("%s",fname);
    
    printf("enter the filesize\n");
    scanf("%d",&size);
    
    for(int i=0;i<totalBlocks;i++)  
    {
        if(disk[i]==0)
        {
            indexBlock=i;
            disk[i]=1;
            break;
        }
    }
    
    if(indexBlock==-1)
    {
        printf("no blocks avaible to be indexblock\n");
        return;
    }
    
    printf("enter %d block number to store the file data\n",size);
    for(int i=0;i<size;i++)
    {
        int b;
        scanf("%d",&b);
        if(b<0||disk[b]==1||b>=totalBlocks)
        {
            printf("no such disk block is avaiable to store data\n");
            return;
        }
        else
        {
            disk[b]=1;
            data[i]=b;
        }
    }
    
    strcpy(file[totalFiles].name,fname);
    file[totalFiles].indexBlock=indexBlock;
    file[totalFiles].size=size;
    for (int i=0;i<size;i++)
    {
    file[totalFiles].dataBlocks[i]=data[i];
    }
    totalFiles++;
    
    
}

void viewFiles()
{
    if(totalFiles==0)
    {
        printf("no files have been allocated\n");
        return;
    }
    else
    {
        for(int i=0;i<totalFiles;i++)
        {
            printf("file name:%s \n",file[i].name);
            printf("file indexblock:%d \n",file[i].indexBlock);
            printf("file data blocks are :\n");
            for(int j=0;j<file[i].size;j++)
            {
                printf("%d",file[i].dataBlocks[j]);
            }
            
        }
    }
}

void viewBlocks()
{
    for (int i=0;i<totalBlocks;i++)
    {
        if (disk[i]==0)
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
    printf("enter the total number of blocks\n");
    scanf("%d",&totalBlocks);
    
    initializeBlocks(totalBlocks);
    
    while(1)
    {
        printf("enter 1 for file allocation\n");
        printf("enter 2 for viewing files\n");
        printf("enter 3 for viewing diskblocks\n");
        printf("enter 4 for exiting\n");
        
        printf("enter your choice\n");
        scanf("%d",&choice);
        
        if (choice==1)
        {
            allocateFiles();
        }
        if (choice==2)
        {
            viewFiles();
        }
        if (choice ==3)
        {
            viewBlocks();
        }
        if (choice==4)
        {
            exit(0);
        }
        
        
    }
}
