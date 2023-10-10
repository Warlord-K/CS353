#include<iostream>
using namespace std;

// Function to calculate waiting time for each process
void calculateWaitingTime(int processes[], int n, int burst_time[], int waiting_time[], int quantum) {
    int remaining_time[n];

    // Initialize remaining_time with burst_time values
    for (int i = 0; i < n; i++) {
        remaining_time[i] = burst_time[i];
    }

    int current_time = 0; // Current time

    while (true) {
        bool all_processes_done = true;

        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                all_processes_done = false; // There is a pending process

                if (remaining_time[i] > quantum) {
                    current_time += quantum;
                    remaining_time[i] -= quantum;
                } else {
                    current_time += remaining_time[i];
                    waiting_time[i] = current_time - burst_time[i];
                    remaining_time[i] = 0;
                }
            }
        }

        if (all_processes_done) {
            break;
        }
    }
}

// Function to calculate turnaround time for each process
void calculateTurnaroundTime(int processes[], int n, int burst_time[], int waiting_time[], int turnaround_time[]) {
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = burst_time[i] + waiting_time[i];
    }
}

// Function to calculate and display average waiting and turnaround times
void calculateAndDisplayAverageTimes(int processes[], int n, int burst_time[], int quantum) {
    int waiting_time[n], turnaround_time[n];
    int total_waiting_time = 0, total_turnaround_time = 0;

    calculateWaitingTime(processes, n, burst_time, waiting_time, quantum);
    calculateTurnaroundTime(processes, n, burst_time, waiting_time, turnaround_time);

    cout << "Process\tBurst Time\tWaiting Time\tTurnaround Time\n";

    for (int i = 0; i < n; i++) {
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];

        cout << processes[i] << "\t\t" << burst_time[i] << "\t\t" << waiting_time[i] << "\t\t" << turnaround_time[i] << endl;
    }

    cout << "Average Waiting Time = " << (float)total_waiting_time / n << endl;
    cout << "Average Turnaround Time = " << (float)total_turnaround_time / n << endl;
}

int main() {
    int processes[] = {1, 2, 3, 4};
    int n = sizeof processes / sizeof processes[0];

    int burst_time[] = {10, 5, 8, 12};
    int quantum = 3;

    calculateAndDisplayAverageTimes(processes, n, burst_time, quantum);

    return 0;
}
