/*

Add synchronization code based on semaphores to process A and B in
question 1 so that there is no possibility of race conditions. Use the calls
semget(), semop(), semctl() to create and manage semaphores.


*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/shm.h>

int P(int semId, int semNum){
    struct sembuf operationList[1];
    operationList[0].sem_num = semNum;
    operationList[0].sem_op = -1;
    operationList[0].sem_flg = 0;
    return semop(semId, operationList, 1);
}

int V(int semId, int semNum){
    struct sembuf operationList[1];
    operationList[0].sem_num = semNum;
    operationList[0].sem_op = 1;
    operationList[0].sem_flg = 0;
    return semop(semId, operationList, 1);
}

int main(){
    
    // Declare the Required Variables: Shared Memory id, X, count and flag to ensure the parent process waits for the child processes to finish
    int shmID;
    int* X;
    int count  = 100000;
    int flag;
    // Declare two semaphores
    int semID1, semID2;

    // Create a shared memory segment and attach it to the variable X
    shmID = shmget(IPC_PRIVATE, sizeof(int), 0666|IPC_CREAT);
    X = (int*)shmat(shmID, NULL, 0);

    // Create two semaphores
    semID1 = semget(IPC_PRIVATE, 1, 0666|IPC_CREAT);
    semID2 = semget(IPC_PRIVATE, 1, 0666|IPC_CREAT);
    semctl(semID1, 0, SETVAL, 0);
    semctl(semID2, 0, SETVAL, 1);

    // Read the value of X from the user
    int n;
    printf("Enter value of X: ");
    scanf("%d", &n);
    *X = n;

    // Create two child processes and increment and decrement the value of X in them
    if(fork() == 0){
        // Process A
        while(count--){
            // Wait for semaphore 1
            P(semID1, 0);
            (*X)++;
            // Signal semaphore 2
            V(semID2, 0);
        }
    }else{
        if(fork() == 0){
            // Process B
            while(count--){
                // Wait for semaphore 2
                P(semID2, 0);
                (*X)--;
                // Signal semaphore 1
                V(semID1, 0);
            }
        }else{
            // Parent Process
            // Wait for both the child processes to finish
            wait(&flag);
            wait(&flag);
            printf("Final Value of X: %d\n", *X);
            // Detach and Delete the shared memory segment
            shmctl(shmID, IPC_RMID, NULL);
        }
    }

    return 0;

}