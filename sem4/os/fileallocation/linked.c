#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct block
{
    int blocknumber;
    struct block * next;
};

struct file
{
    char fname[10];
    int size;
    struct block * head;
};

struct file files[MAX];
int disks[MAX];
int totalfiles=0,totalblocks=0,ch=0;


struct block * createblock(int b)
{
    struct block * newblock=(struct block*)malloc(sizeof(struct block));
    newblock->blocknumber=b;
    newblock->next=NULL;
    return newblock;
}

void allocateFiles()
{
    int size;
    char fname[20];
    
    printf("enter the filename\n");
    scanf("%s",fname);
    printf("enter the filesize\n");
    scanf("%d",&size);
    
    struct block * head=NULL;
    
    printf("enter the %d data blocks to allocate file\n",size);
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
            struct block * newblock = createblock(b);
            
            if(head==NULL)
            {
                head=newblock;
            }
            else
            {
                struct block * temp=head;
                while(temp->next!=NULL)
                {
                    temp=temp->next;
                }
                temp->next=newblock;
            }
        }
    
    }
    strcpy(files[totalfiles].fname,fname);
    files[totalfiles].head=head;
    files[totalfiles].size=size;
    totalfiles++;
}

void viewFiles()
{
    if(totalfiles==0)
    {
        printf("no files have been allocated yet\n");
        return;
    }
    else
    {
        for(int i=0;i<totalfiles;i++)
        {
            printf("details of file %d are:\n",(i+1));
            printf("filename is %s\n:",files[i].fname);
            printf("file size is %d:\n",files[i].size);
            printf("file data blocks list is:\t\t\t");
            struct block * temp=files[i].head;
            while(temp!=NULL)
            {
                printf("%d->",temp->blocknumber);
                temp=temp->next;
            }
        }
        printf("\n");
    }
}
void viewBlocks()
{
    for(int i=0;i<totalblocks;i++)
    {
        if(disks[i]==0)
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