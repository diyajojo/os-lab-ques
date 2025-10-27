#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct file
{
    char fname[10];
    int indexblock;
    int datablocks[MAX];
    int size;
};

struct file files[MAX];
int disks[MAX],data[MAX];

int totalfiles=0,totalblocks=0,ch=0;



void allocateFiles()
{
    int size,indexblock=-1;
    char fname[20];
    
    printf("enter file name\n");
    scanf("%s",fname);
    printf("enter file size\n");
    scanf("%d",&size);
    
    for(int i=0;i<totalblocks;i++)
    {
        if(disks[i]==0)
        {
            indexblock=i;
            disks[i]=1;
            break;
        }
    }
    
    if(indexblock==-1)
    {
        printf("there is no index block available , file allocation isnt possible\n");
        return;
    }
    else
    {
        printf("enter the %d data blocks index to store the file in disks\n",size);
        for(int i=0;i<size;i++)
        {
            int b;
            scanf("%d",&b);
            if(b<0 || b>totalblocks || disks[b]==1)
            {
                printf("disk block in use , file cant be allocated\n");
                return;
            }
            else
            {
                disks[b]=1;
                data[i]=b;
            }
        }
        
        strcpy(files[totalfiles].fname,fname);
        files[totalfiles].indexblock=indexblock;
        files[totalfiles].size=size;
        for(int i=0;i<size;i++)
        {
            files[totalfiles].datablocks[i]=data[i];
        }
        totalfiles++;
    }
}
void viewFiles()
{
    if(totalfiles==0)
    {
        printf("no files have been allocated\n");
        return;
    }
    else
    {
        for(int i=0;i<totalfiles;i++)
        {
            printf("file name:%s \n",files[i].fname);
            printf("file indexblock:%d \n",files[i].indexblock);
            printf("file data blocks are :\t");
            for(int j=0;j<files[i].size;j++)
            {
                printf("%d\t",files[i].datablocks[j]);
            }
            printf("\n");
        }
    }
}

void viewBlocks()
{
    for (int i=0;i<totalblocks;i++)
    {
        if (disks[i]==0)
        {
            printf("disk %d is free\n",i);
        }
        else
        {
            printf("disk %d is not free\n",i);
        }
    }
}


void main()
{
    printf("enter the number of disk blocks\n");
    scanf("%d",&totalblocks);
    
    for(int i=0;i<totalblocks;i++)
    {
        disks[i]=0;
    }
    while(1)
    {
        printf("menu driven program\n");
        printf("1 for file allocation \n");
        printf("2 for viewing allocated files\n");
        printf("3 for viewing disk blocks\n");
        printf("enter your choice\n");
        scanf("%d",&ch);
        
        if(ch==1)
        {
            allocateFiles();
        }
        else if(ch==2)
        {
            viewFiles();
        }
        else if(ch==3)
        {
            viewBlocks();
        }
        else
        {
            printf("invalid choice\n");
            exit(0);
        }
    }
}