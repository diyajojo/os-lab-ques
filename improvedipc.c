#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

//memory size
#define SIZE 10

int main()
{
    key_t key;
    int shmid;
    char *shm;


    // perror is used to print the error message (like printf) and exit(1) is used to exit the program


    // Generate unique key
    // ftok generates a key based on a file and a char (makes it unique)
    key = ftok("filea", 'R');
    if (key == -1) 
    {
        perror("ftok failed");
        exit(1);
    }

    // Create shared memory segment or include existing one (shmget)
    //IPC_CREAT is used to create a new shared memory segment and 0666 is permission to read / write
    shmid = shmget(key, SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }

    // Attach shared memory to memory space (shmat)
    // NULL is used to let the system choose the address and 0 is used to read/write
    shm = shmat(shmid, NULL, 0);
    if (shm == (char *)-1) {
        perror("shmat failed");
        exit(1);
    }

    // Write to shared memory
    sprintf(shm, "written");

    // Detach shared memory (shmdt)
    if (shmdt(shm) == -1) 
    {
        perror("shmdt failed");
        exit(1);
    }

    // Remove shared memory segment
    // shmctl is used to control shared memory and IPC_RMID is used to remove the shared memory
    if (shmctl(shmid, IPC_RMID, NULL) == -1) 
    {
        perror("shmctl failed");
        exit(1);
    }

    return 0;
}
