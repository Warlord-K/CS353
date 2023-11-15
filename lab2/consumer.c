#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

#define SHMSIZE 27

int main() {
    char *s, *shm;
    key_t key = 6190;
    int shmid = shmget(key, SHMSIZE, 0666);
    shm = (char*) shmat(shmid, NULL, 0);

    for(s=shm; *s!=0; s++) {
        putchar(*s);
    }
	//printf("here\n");
    putchar('\n');

    *shm = '*';
    shmdt(s);
    shmctl(shmid, IPC_RMID, NULL);
    exit(0);
}
