/*
Implement Round robin cpu scheduling algorithm with time quantum 3 units in C language.

Input - The program should take process ID, arrival time, and burst time of 5 processes from the
user.
Output - The expected output is a Gantt chart of the schedule and average waiting time and the
average turnaround time of those processes .

*/

#include <stdio.h>
#include <stdlib.h>

struct process{
    int id;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
    int remainingTime;
};

int main(){
    int n = 5;
    struct process* processes = (struct process*)malloc(n*sizeof(struct process));
    int i;

    for(i=0; i<n; i++){
        printf("Enter Process ID, Arrival Time and Burst Time of Process %d: ", i+1);
        scanf("%d%d%d", &processes[i].id, &processes[i].arrivalTime, &processes[i].burstTime);
        processes[i].remainingTime = processes[i].burstTime;
    }

    int time = 0;
    int completed = 0;
    int quantum = 3;
    int flag = 0;
    int j;
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    while(completed < n){
        flag = 0;
        for(i=0; i<n; i++){
            if(processes[i].arrivalTime <= time && processes[i].remainingTime > 0){
                flag = 1;
                if(processes[i].remainingTime > quantum){
                    time += quantum;
                    processes[i].remainingTime -= quantum;
                }else{
                    time += processes[i].remainingTime;
                    processes[i].remainingTime = 0;
                    processes[i].waitingTime = time - processes[i].burstTime - processes[i].arrivalTime;
                    processes[i].turnaroundTime = time - processes[i].arrivalTime;
                    totalWaitingTime += processes[i].waitingTime;
                    totalTurnaroundTime += processes[i].turnaroundTime;
                    completed++;
                }
            }
        }
        if(flag == 0){
            time++;
        }
    }

    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for(i=0; i<n; i++){
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrivalTime, processes[i].burstTime, processes[i].waitingTime, processes[i].turnaroundTime);
    }
    printf("Average Waiting Time: %f\n", (float)totalWaitingTime/n);
    printf("Average Turnaround Time: %f\n", (float)totalTurnaroundTime/n);
    
    return 0;
}


