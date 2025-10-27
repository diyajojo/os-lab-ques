#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000

int np,nb,ch,blockSize[SIZE],processSize[SIZE],allocated[SIZE];


struct node
{
    int index;
    int size;
    struct node *next;
};

void firstFit(struct node * head,int processSize[],int np)
{
    for(int i=0;i<np;i++)
    {
        allocated[i]=-1;
    }
    
    for(int i=0;i<np;i++)
    {
        struct node *temp=head;
        while(temp!=NULL)
        {
            if(temp->size>=processSize[i])
            {
                temp->size -= processSize[i];
                allocated[i]=(temp->index)+1;
                break;
            }
            temp=temp->next;
        }
    }
    printf("PROCESS NO\t\t\t\tMEMORY BLOCK\n");
    for (int i=0;i<np;i++)
    {
        printf("P%d\t\t\t",(i+1));
        if(allocated[i]!=-1)
        {
           printf("%d\n",allocated[i]); 
        }
        else
        {
            printf("memory not allocated\n");
        }
    }
}



void bestFit(struct node * head,int processSize[],int np)
{
    for(int i=0;i<np;i++)
    {
        allocated[i]=-1;
    }
    
    for(int i=0;i<np;i++)
    {
        struct node *temp=head;
        struct node* bestblock=NULL;
        while(temp!=NULL)
        {
            if(bestblock==NULL || temp->size <bestblock->size)
            {
                bestblock=temp;
            }
            temp=temp->next;
        }
        if(bestblock!=NULL)
        {
            bestblock->size-=processSize[i];
            allocated[i]=(bestblock->index)+1;
        }
    }
    printf("PROCESS NO\t\t\t\tMEMORY BLOCK\n");
    for (int i=0;i<np;i++)
    {
        printf("P%d\t\t\t",(i+1));
        if(allocated[i]!=-1)
        {
           printf("%d\n",allocated[i]); 
        }
        else
        {
            printf("memory not allocated\n");
        }
    }
}

void worstFit(struct node * head,int processSize[],int np)
{
    for(int i=0;i<np;i++)
    {
        allocated[i]=-1;
    }
    
    for(int i=0;i<np;i++)
    {
        struct node *temp=head;
        struct node* worstblock=NULL;
        while(temp!=NULL)
        {
            if(worstblock==NULL || temp->size > worstblock->size)
            {
                worstblock=temp;
            }
            temp=temp->next;
        }
        if(worstblock!=NULL)
        {
            worstblock->size-=processSize[i];
            allocated[i]=(worstblock->index)+1;
        }
    }
    printf("PROCESS NO\t\t\t\tMEMORY BLOCK\n");
    for (int i=0;i<np;i++)
    {
        printf("P%d\t\t\t",(i+1));
        if(allocated[i]!=-1)
        {
           printf("%d\n",allocated[i]); 
        }
        else
        {
            printf("memory not allocated\n");
        }
    }
}


void insertMemory(struct node **head,int size,int index)
{
    struct node*newblock=(struct node *)malloc(sizeof(struct node));
    newblock->index=index;
    newblock->size=size;
    newblock->next=NULL;
    
    if(*head==NULL)
    {
        *head=newblock;
    }
    else
    {
        struct node * temp = *head;
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=newblock;
    }
}


struct node * createMemory(int blockSize[],int nb)
{
    struct node* head=NULL;
    for(int i=0;i<nb;i++)
    {
        insertMemory(&head,blockSize[i],i);
    }
    return head;
}
int main()
{
    printf("enter the number of memeory blocks\n");
    scanf("%d",&nb);
    
    for(int i=0;i<nb;i++)
    {
        printf("enter the size of memory block %d:\n",(i+1));
        scanf("%d",&blockSize[i]);
    }
    
    printf("enter the number of processes\n");
    scanf("%d",&np);
    
    for(int i=0;i<np;i++)
    {
        printf("enter the size of process %d:\n",(i+1));
        scanf("%d",&processSize[i]);
    }
    
    
    do
    {
    printf("menu-driven program\n");
    printf("press 1 for firstfit\n");
    printf("press 2 for bestfit\n");
    printf("press 3 for worstfit\n");
    printf("press 4 to exit\n");
    
    
    printf("enter choice:\n");
    scanf("%d",&ch);
    
    struct node *head =createMemory(blockSize,nb);
    
    switch(ch)
    {
        case 1:
        firstFit(head,processSize,np);
        break;
        
        case 2:
        bestFit(head,processSize,np);
        break;
        
        case 3:
        worstFit(head,processSize,np);
        break;
        
        case 4:
        exit(0);
        
        default:
        printf("invalid choice\n");
        
        struct node *temp ;
        
        while(head!=NULL)
        {
            temp=head;
            head=head->next;
            free(temp);
        }
    }
 }
    while(ch!=4);
    
    return 0;
}
