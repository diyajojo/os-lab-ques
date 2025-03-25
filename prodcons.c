#include <stdio.h>
#include <stdlib.h>  // for rand() to generate random numbers
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // to call the sleep function

#define SIZE 5

int buffer[SIZE];
int in = 0, out = 0;

sem_t mutex, full, empty;

// function both return NULL becuase return type is void* and they are called by the threads
void *producer(void *arg) 
{
    for (int i = 0; i < 5; i++) {
        int item = rand() % 100; // Generate a random item

        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[in] = item;
        printf("Item produced: %d\n", item);
        in = (in + 1) % SIZE; // Circular buffer

        sem_post(&mutex);
        sem_post(&full);

        sleep(1);
    }
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 0; i < 5; i++) {
        sem_wait(&full);
        sem_wait(&mutex);

        int item = buffer[out]; // Read item from buffer
        printf("Item consumed: %d\n", item);
        out = (out + 1) % SIZE; // Circular buffer

        sem_post(&mutex);
        sem_post(&empty);

        sleep(1);
    }
    return NULL;
}

int main() {

    pthread_t prod, cons;


    sem_init(&mutex, 0, 1); // 1 indicates mutex is available
    sem_init(&empty, 0, 0); // 0 indicates buffer is empty
    sem_init(&full, 0, SIZE);// SIZE indicates buffer is full , the max value taken by full 

// producer and cosnumer are the functions that are called by the threads with NULL arguements
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
