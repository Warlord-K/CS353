#include <iostream>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
using namespace std;

int main(){
	
	int shmid = shmget((key_t) 5670, sizeof(int), 0666|IPC_CREAT);
	int f = fork();
	int *shared_memory = (int *) shmat(shmid, NULL, 0);
	if(f){
			cout << "Parent Here" << endl;
			*shared_memory = 7;
			cout << *shared_memory << endl;
	}else{
			cout << "Child here" << endl;
			cout << "Hello" << endl;
			cout << *shared_memory << endl;
	}
	shmdt(shared_memory);
	if(f){	
	shmctl(shmid, IPC_RMID, NULL);
	}
	//shmget
	//shmctl
	//shmat
	//shmdt
	return 0;
}
