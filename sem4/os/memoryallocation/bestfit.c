#include <stdio.h>
#include <stdlib.h>

struct node
{
    int index;
    int size;
    struct node * next;
};

struct node * head=NULL;

void insertMemory(struct node ** head, int size,int index)
{
    struct node * newblock=(struct node*)malloc(sizeof(struct node));
    newblock->size=size;
    newblock->index=index;
    newblock->next=NULL;
    
    if(*head==NULL)
    {
        *head=newblock;
    }
    else
    {
        struct node*temp=*head;
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=newblock;
    }
}

void bestFit(struct node *head,int processSize[],int np)
{
    int allocated[np];
    for(int i=0;i<np;i++)
    {
        allocated[i]=-1;
    }
    for(int i=0;i<np;i++)
    {
        struct node * temp=head;
        struct node *bestBlock=NULL;
        
        while(temp!=NULL)
        {
            if(temp->size>=processSize[i])
            {
                if(bestBlock==NULL || temp->size < bestBlock->size)
                {
                    bestBlock=temp;
                }
            }
            temp=temp->next;
        }
        
        if(bestBlock!=NULL)
        {
            bestBlock->size -= processSize[i];
            allocated[i]=(bestBlock->index)+1;
        }
    }
   printf("\nprocess-size\t\tblock-no\n");
   for (int i = 0; i < np; i++)
    {
    printf("%d\t\t\t\t", processSize[i]);
    if (allocated[i] != -1)
    {
        printf("%d\n", allocated[i]);
    }
    else
    {
        printf("process not allocated memory yet\n");
    }
}
}


int main()
{
    int nb,np;
    
    printf("enter the number of memory blocks\n");
    scanf("%d",&nb);
    
    for(int i=0;i<nb;i++)
    {
        int size;
        printf("enter the size of memory block %d\n",(i+1));
        scanf("%d",&size);
        insertMemory(&head,size,i);
    }
    
    printf("enter the number of process\n");
    scanf("%d",&np);
    
    int processSize[np];
    
    for(int i=0;i<np;i++)
    {
        printf("enter the size of process %d\n",(i+1));
        scanf("%d",&processSize[i]);
    }
    
    bestFit(head,processSize,np);
    return 0;
}