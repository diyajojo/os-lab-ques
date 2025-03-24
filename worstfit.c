#include <stdio.h>

#define SIZE 10

int allocated[SIZE];

void worstFit(int blockSize[],int nb,int processSize[],int np)
{
   for(int i=0;i<np;i++)
   {
       allocated[i]=-1;
   }
   for(int i=0;i<np;i++)
   {
       int maxIndex=-1;
       for(int j=0;j<nb;j++)
       {
           if(maxIndex=-1 || blockSize[j]>blockSize[maxIndex])
           {
               maxIndex=j;
           }
       }
       if(maxIndex!=-1)
       {
           allocated[i]=maxIndex;
           blockSize[maxIndex]-=processSize[i];
       }
   }
   
   printf("Process size\t\tBlock number\n");
   for(int i=0;i<np;i++)
   {
       printf("%d\t\t\t\t\t\t",processSize[i]);
       if(allocated[i]!=-1)
       {
           printf("%d\n",allocated[i]);
       }
       else
       {
           printf("not allocated");
       }
   }
}



int main()
{
    int blockSize[] = {250, 30, 456, 212, 117};
    int processSize[] = {100, 200, 300, 400};
    int nb = sizeof(blockSize) / sizeof(blockSize[0]);
    int np = sizeof(processSize) / sizeof(processSize[0]);

    worstFit(blockSize, nb, processSize, np);

    return 0;
}
