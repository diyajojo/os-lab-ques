#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXBLOCKS 100
#define MAXFILES 100

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

int disks[MAXBLOCKS];
struct file files[MAXFILES];
int totalblocks , totalfiles;
int choice;

void initializeBlocks (int totalblocks)
{
    for(int i=0;i<totalblocks;i++)
    {
        disks[i]=0;
    }
}

struct block * createblock(int blocknumber )
{
    struct block* newblock=(struct block*)malloc(sizeof(struct block));
    newblock->blocknumber=blocknumber;
    newblock->next=NULL;
    disks[blocknumber]=1;
    return newblock;
}

void allocateFile()
{
    char fname[20];
    int size;
    
    printf("enter file name\n");
    scanf("%s",fname);
    
    printf("enter file size\n");
    scanf("%d",&size);
    
    struct block * head=NULL;
    struct block * current=NULL;
    
    printf("enter the %d blocks in which file is to be places\n",size);
    
    for(int i=0;i<size;i++)
    {
        int b;
        scanf("%d",&b);
        struct block * newblock=createblock(b);
        
        if(head==NULL)
        {
            head=newblock;
        }
        else
        {
            current->next=newblock;
        }
        current=newblock;
    }
    strcpy(files[totalfiles].fname,fname);
    files[totalfiles].head=head;
    totalfiles++;
}

void viewFile()
{
    if(totalfiles==0)
    {
        printf("no files are allocated yet\n");
    }
    else
    {
        for(int i=0;i<totalfiles;i++)
        {
             printf("details of the  file %d are:\n",(i+1));
            printf("file name is %s:\n",files[i].fname);
            struct block * temp =files[i].head;
            while(temp!=NULL)
            {
                printf("%d->",temp->blocknumber);
                temp=temp->next;
            }
            printf("null\n");
        }
    }
}
void viewBlock()
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

int main()
{
    printf("enter total number of blocks\n");
    scanf("%d",&totalblocks);
    
    initializeBlocks(totalblocks);
    
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
