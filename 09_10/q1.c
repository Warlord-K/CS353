#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <unistd.h>

int main(){

    // Declare the Required Variables: Shared Memory id, X, count and flag to ensure the parent process waits for the child processes to finish
    int shmID;
    int* X;
    int count  = 100000;
    int flag;
    
    // Create a shared memory segment and attach it to the variable X
    shmID = shmget(IPC_PRIVATE, sizeof(int), 0666|IPC_CREAT);
    X = (int*)shmat(shmID, NULL, 0);

    // Read the value of X from the user
    int n;
    printf("Enter value of X: ");
    scanf("%d", &n);
    *X = n;

    // Create two child processes and increment and decrement the value of X in them
    if(fork() == 0){
        // First Process
        while(count--){
            (*X)++;
        }
    }else{
        if(fork() == 0){
            // Second Process
            while(count--){
                (*X)--;
            }
        }else{
            // Parent Process
            wait(&flag);
            wait(&flag);
            printf("Final Value of X: %d\n", *X);
            // Detach and Delete the shared memory segment
            shmctl(shmID, IPC_RMID, NULL);
        }
    }

    return 0;
}