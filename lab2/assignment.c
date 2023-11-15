#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<bits/stdc++.h>
#define SHMSIZE 40

int main() {
    int *shm;
    int s[10];
    key_t key = 6123;
    for(int i = 0; i < 10; i++) {
        scanf("%d",(s+i));
    }
    int f1 = fork();
    int f2 = 1;
    if(f1){
    f2 = fork();
    if(f2){
    	int shmid = shmget(key, SHMSIZE, 0666|IPC_CREAT);
		shm = (int*) shmat(shmid, NULL, 0);
		for(int i = 0; i < 10; i++) {
		    *(shm+i) = s[i];
		}
    }
    }
    if(!f1){
    	quiksort(shm, shm + 5);
    }
    if(!f2){
    	quicksort(shm + 5, shm + 10);
    }
    if(f1 && f2){
    	merge(shm, shm + 5, shm + 5, shm + 10);
    }
    for(int i = 0; i < 10; i++){    
	printf("%d ", *(shm+i));
    }
    printf("\n");
    shmdt(shm);
    shmctl(shmid, IPC_RMID, NULL);
    exit(0);
}