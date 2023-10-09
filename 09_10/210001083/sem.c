#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/sem.h>

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
    int semID1, semID2;
    int flag;
    char* str;
    int count  = 10;
    FILE* fp;
    int data=0;

    semID1 = semget(IPC_PRIVATE, 1, 0666|IPC_CREAT);
    semID2 = semget(IPC_PRIVATE, 1, 0666|IPC_CREAT);
    semctl(semID1, 0, SETVAL, 0);
    semctl(semID2, 0, SETVAL, 1);
    if(fork() == 0){
        while(count--){
            P(semID1, 0);
            fp = fopen("file.txt", "r");
            fscanf(fp, "%d", &data);
            fclose(fp);
            printf("child read %d\n", data);
            V(semID2, 0);
        }
    }else{
        while(count--){
            sleep(1);
            P(semID2, 0);
            fp = fopen("file.txt", "w");
            fprintf(fp, "%d", ++data);
            fclose(fp);
            printf("parent write %d\n", data);
            V(semID1, 0);
        }
        wait(&flag);
    }

    return 0;
}