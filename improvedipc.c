#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SIZE 10

int main()
{
    key_t key;
    int shmid;
    char *shm;
    
    // Generate unique key
    key = ftok("filea", 'R');
    if (key == -1) {
        perror("ftok failed");
        exit(1);
    }

    // Create shared memory segment with correct permissions
    shmid = shmget(key, SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }

    // Attach shared memory
    shm = shmat(shmid, NULL, 0);
    if (shm == (char *)-1) {
        perror("shmat failed");
        exit(1);
    }

    // Write to shared memory
    sprintf(shm, "written");

    // Detach shared memory
    if (shmdt(shm) == -1) {
        perror("shmdt failed");
        exit(1);
    }

    // Remove shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl failed");
        exit(1);
    }

    return 0;
}
