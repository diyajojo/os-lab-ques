#include <stdio.h>
#include <stdlib.h>

struct node *head=NULL;

struct node 
{
    int index;
    int size;
    struct node* next;
}


void insertMemoryblock(struct node** head, int size, int index)
{
    struct node* newnode=(struct node*)malloc(sizeof(struct node));
    newnode->index=index;
    newnode->size=size;
    newnode->next=NULL;

    if(*head==NULL)
    {
        *head=newnode;
    }
    else
    {
        struct node * temp =head;
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=newnode;
    }

}

void firstFit(struct node* head,int processSize[],int np)
{
  
  int allocated[np];
  for(int i=0;i<np;i++)
  {
    allocated[i]=-1;
  }

  for (int i=0;i<np;i++)
  {
    struct node*temp=head;
    while(temp!=NULL)
    {
        if(temp->size>=processSize[i])
        {
            temp->size-=processSize[i];
            allocated[i]=temp->index;
            break;
        }
        temp=temp->next;
    }
  }

  printf("process-size\t\tblock-no\n");
  for(int i=0;i<np;i++)
  {
    printf("%d\t\t\t\t",processSize[i]);
    if (allocated[i]!=1)
    {
        printf("%d",allocated[i]);
    }
    else
    {
        printf("process not allocated memory yet");
    }
  }
}



int main()
{
  int np,nb;

  printf("enter the number of memory blocks\n");
  scanf("%d",&nb);

  for(int i=0;i<nb;i++)
  {
    int size;
    printf("enter the size of the memory block%d\n",(i+1));
    scanf("%d",&size);
    insertMemoryblock(&head,size,i);
  }

  printf("enter the process size\n");
  scanf("%d",&np);

  int processSize[np];

  for(int i=0;i<np;i++)
  {
    printf("enter the size of process %d\n",(i+1));
    scanf("%d",&processSize[i]);
  }

  firstFit(head,processSize,np)

  return 0;
}