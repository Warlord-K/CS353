/*

Consider a system with one parent process and two child processes A and B.
There is a shared signed integer X (assign value through user input). Process A
increments X by one, 100000 times in a for loop. Process B decrements X by one,
100000 times in a for loop. After both A and B finish, the parent process prints the
final value of X.
Hint: Declare a shared memory variable to hold X (using system calls shmget(),
shmat(), shmdt(), and shmctl()). Write the programs for processes A and B. Do not
put any synchronization code in the code for A and B. You should write the code in
such a way so that you can simulate race condition in your program by slowing
down A or B appropriately by using sleep() calls at appropriate points. Note that if
there is no race condition, the value of X finally should be the one given through
user input. Simulating race conditions means that if you run the program a few
times, sometimes the final value of X printed by your program should be non-zero.


*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>


int main(){
    int shmID;
    int* X;
    int count  = 100000;
    int flag;
    int pid1, pid2;
    
    shmID = shmget(IPC_PRIVATE, sizeof(int), 0666|IPC_CREAT);
    X = (int*)shmat(shmID, NULL, 0);
    *X = 0;

    if((pid1 = fork()) == 0){
        while(count--){
            (*X)++;
        }
    }else{
        if((pid2 = fork()) == 0){
            while(count--){
                (*X)--;
            }
        }else{
            wait(&flag);
            wait(&flag);
            printf("final value of X: %d\n", *X);
            shmctl(shmID, IPC_RMID, NULL);
        }
    }

    return 0;
}