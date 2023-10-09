/*

Implement SRTF(Shortest Remaining Time First) i.e, Preemptive version of SJF cpu scheduling
algorithm in c language.
Input - The program should take process ID, arrival time, and burst time of 5 processes from the
user.
Output - The expected output is a Gantt chart of the schedule and average waiting time and the
average turnaround time of those processes .

*/

#include <stdio.h>
#include <stdlib.h>

// Process Structure
struct process{
    int id;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
    int remainingTime;
};

int main(){
    // Declare and Initialize Variables
    int n = 3;
    struct process* processes = (struct process*)malloc(n*sizeof(struct process));
    int i, j;

    // Read the process details from the user
    for(i=0; i<n; i++){
        printf("Enter Process ID, Arrival Time and Burst Time of Process %d: ", i+1);
        scanf("%d%d%d", &processes[i].id, &processes[i].arrivalTime, &processes[i].burstTime);
        processes[i].remainingTime = processes[i].burstTime;
    }

    // Sort the processes according to their arrival time
    for(i=0; i<n; i++){
        for(j=0; j<n-i-1; j++){
            if(processes[j].arrivalTime > processes[j+1].arrivalTime){
                struct process temp = processes[j];
                processes[j] = processes[j+1];
                processes[j+1] = temp;
            }
        }
    }

    int time = 0;
    int completed = 0;
    int flag = 0;
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    // Run the scheduler
    while(completed < n){
        flag = 0;
        for(i=0; i<n; i++){
            if(processes[i].arrivalTime <= time && processes[i].remainingTime > 0){
                flag = 1;
                break;
            }
        }
        if(flag == 0){
            time++;
            continue;
        }
        int minRemainingTime = processes[i].remainingTime;
        int minIndex = i;
        for(int j=i+1; j<n; j++){
            if(processes[j].arrivalTime <= time && processes[j].remainingTime > 0 && processes[j].remainingTime < minRemainingTime){
                minRemainingTime = processes[j].remainingTime;
                minIndex = j;
            }
        }
        processes[minIndex].remainingTime--;
        if(processes[minIndex].remainingTime == 0){
            completed++;
            processes[minIndex].waitingTime = time - processes[minIndex].arrivalTime - processes[minIndex].burstTime;
            processes[minIndex].turnaroundTime = time - processes[minIndex].arrivalTime;
            totalWaitingTime += processes[minIndex].waitingTime;
            totalTurnaroundTime += processes[minIndex].turnaroundTime;
        }
        time++;
    }

    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for(i=0; i<n; i++){
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrivalTime, processes[i].burstTime, processes[i].waitingTime, processes[i].turnaroundTime);
    }
    printf("Average Waiting Time: %f\n", (float)totalWaitingTime/n);
    printf("Average Turnaround Time: %f\n", (float)totalTurnaroundTime/n);


    

    return 0;
}