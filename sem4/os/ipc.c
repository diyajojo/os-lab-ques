#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define  SIZE 10

int main()
{
    key_t key;
    int shmid;
    char * shm;

    key=ftok("shmfile",'R');
    shmid=shmget(key,SIZE, IPC_CREAT | 0666 );
    shm=shmat(shmid, NULL,0);

    sprintf(shm,"hello im writing to shared memory \n");

    shmdt(shm);

    return 0
}


#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SIZE 10

int main()
{
    key_t key=ftok("shmfile",'R');
    int shmid=shmget(key,SIZE,0666);

    if(shmid==-1)
    {
        perror("no memory exists");
        exit(0);
    }
     char *shm=shmat(shmid,NULL,0);

     if(shm == (char*)1)
     {
        perror("cant attach the shared memory");
        exit(0);
     }

     sprintf(shm,"entered the shared memory");

     shmdt(shm);

     shmctl(shmid, IPC_RMID,NULL);
}


