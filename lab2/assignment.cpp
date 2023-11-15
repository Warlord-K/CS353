#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<bits/stdc++.h>
#include<sys/wait.h>
#define SHMSIZE 40
using namespace std;
int main() {
    int *shm;
    int shmid;
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
    	shmid = shmget(key, SHMSIZE, 0666|IPC_CREAT);
		shm = (int*) shmat(shmid, NULL, 0);
		for(int i = 0; i < 10; i++) {
		    *(shm+i) = s[i];
		}
    }
    }
	if(!f1){
		shmid = shmget(key, SHMSIZE, 0666|IPC_CREAT);
		shm = (int*) shmat(shmid, NULL, 0);
		cout << "Comment Me and Have Fun" << endl;
		sort(shm, shm + 5);
    	shmdt(shm);
    	exit(0);
    }
    if(!f2){
    	shmid = shmget(key, SHMSIZE, 0666| IPC_CREAT);
		shm = (int*) shmat(shmid, NULL, 0);
    	sort(shm+5, shm+10);
    	shmdt(shm);
    	exit(0);
    }
    int arr[10];
    if(f1 && f2){
    	wait(NULL);
    	merge(shm, shm + 5, shm + 5, shm + 10, arr);
    }
    for(int i = 0; i < 10; i++){    
	printf("%d ", *(arr+i));
    }
    printf("\n");
    shmdt(shm);
    shmctl(shmid, IPC_RMID, NULL);
    exit(0);
}
