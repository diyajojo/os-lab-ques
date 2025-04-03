#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

# define BUFFER 5

int in =0, out=0;
int buffer[BUFFER];

pthread_t prod,cons;
sem_t mutex,empty,full;



void * producer(void *arg)
{
  for(int i=0;i<5;i++)
  {
      int item=rand()%100;
      printf("producer produced: %d\n",item);
      
      sem_wait(&empty);
      sem_wait(&mutex);
      
      buffer[in]=item;
      in= (in+1) % BUFFER;
      
      sem_post(&mutex);
      sem_post(&full);
      
      sleep(1);
      
  }
  
  return NULL;
}

void * consumer(void * arg)
{
    for(int i=0;i<5;i++)
    {
        sem_wait(&full);
        sem_wait(&mutex);
        
        int item=buffer[out];
        printf("consumer consumed:%d\n",item);
        out=(out+1)% BUFFER;
        
        sem_post(&mutex);
        sem_post(&empty);
        
        sleep(1);
    }
    
    return NULL;
}

int main()
{
    // second parameter is 0 , because all the threads are in one process

    sem_init(&mutex,0,1); // 3rd parameter is one indicating the mutex is available initially
    sem_init(&empty,0,BUFFER); // 3rd parameter is BUFFER , means initilal empty slots in the buffer
    sem_init(&full,0,0); // 3rd parameter is 0, means no slots are full initially
    
    pthread_create(&prod,NULL,producer,NULL);
    pthread_create(&cons,NULL,consumer,NULL);
    
    pthread_join(prod,NULL);
    pthread_join(cons,NULL);
    
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    
    return 0;
}