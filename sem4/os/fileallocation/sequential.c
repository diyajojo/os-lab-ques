#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct file
{
    char fname[10];
    int start;
    int end;
};

struct file files[MAX] ;
int disks[MAX];
int totalfiles=0,totalblocks=0,ch=0;


void allocateFiles()
{
    int size,start=-1,count=0;
    char fname[10];
    
    printf("enter file name\n");
    scanf("%s",fname);
    printf("enter file size\n");
    scanf("%d",&size);
    
    for(int i=0;i<totalblocks;i++)
    {
        if(disks[i]==0)
        {
            if(start==-1)
            {
                start=i;
            }
            count++;
            if(count==size)
            {
                for(int j=start;j<(start+size);j++)
                {
                    disks[j]=1;
                }
                strcpy(files[totalfiles].fname,fname);
                files[totalfiles].start=start;
                files[totalfiles].end=start+size-1;
                totalfiles++;
            }
        }
        else
        {
            start=-1;
            count=0;
        }
    }
}

void viewFiles()
{
    for(int i=0;i<totalfiles;i++)
    {
        printf("details of file %d are:\n",(i+1));
        printf("file name is :%s\n",files[i].fname);
        printf("file startblock is :%d\n",files[i].start);
        printf("file endblock is :%d\n",files[i].end);
    }
}

void viewBlocks()
{
    for(int i=0;i<totalblocks;i++)
    {
        if(disks[i]==0)
        {
            printf("block %d is free\n",(i+1));
        }
        else
        {
            printf("block %d is not free\n",(i+1));
        }
    }
}


void main()
{
    printf("enter the total number of disk blocks\n");
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