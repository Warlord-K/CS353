#include <iostream>
#include <climits>
using namespace std;

struct Process {
    int pid; // Process ID
    int bt;  // Burst Time
    int art; // Arrival Time
};

// Function to calculate waiting time for all processes
void calculateWaitingTime(Process proc[], int n, int wt[]) {
    int rt[n];

    // Copy the burst time into rt[]
    for (int i = 0; i < n; i++)
        rt[i] = proc[i].bt;

    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0, finish_time;
    bool check = false;

    // Process until all processes are completed
    while (complete != n) {
        // Find the process with the minimum remaining time
        for (int j = 0; j < n; j++) {
            if ((proc[j].art <= t) && (rt[j] < minm) && rt[j] > 0) {
                minm = rt[j];
                shortest = j;
                check = true;
            }
        }

        if (check == false) {
            t++;
            continue;
        }

        // Reduce remaining time by one
        rt[shortest]--;

        // Update minimum
        minm = rt[shortest];
        if (minm == 0)
            minm = INT_MAX;

        // If a process is completed
        if (rt[shortest] == 0) {
            complete++;
            check = false;

            // Find finish time of the current process
            finish_time = t + 1;

            // Calculate waiting time
            wt[shortest] = finish_time - proc[shortest].bt - proc[shortest].art;

            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }
        t++;
    }
}

// Function to calculate turnaround time
void calculateTurnAroundTime(Process proc[], int n, int wt[], int tat[]) {
    // Calculate turnaround time by adding bt[i] + wt[i]
    for (int i = 0; i < n; i++)
        tat[i] = proc[i].bt + wt[i];
}

// Function to calculate and display average time
void calculateAndDisplayAverageTimes(Process proc[], int n) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    // Calculate waiting time for all processes
    calculateWaitingTime(proc, n, wt);

    // Calculate turnaround time for all processes
    calculateTurnAroundTime(proc, n, wt, tat);

    cout << "Process\tBurst Time\tWaiting Time\tTurnaround Time\n";

    // Calculate total waiting time and total turnaround time
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        cout << proc[i].pid << "\t" << proc[i].bt << "\t\t" << wt[i] << "\t\t" << tat[i] << endl;
    }

    cout << "\nAverage waiting time = " << (float)total_wt / (float)n;
    cout << "\nAverage turnaround time = " << (float)total_tat / (float)n<<endl;
}

int main() {
    Process proc[] = { { 1, 6, 2 }, { 2, 2, 5 },
                      { 3, 8, 1 }, { 4, 3, 0 }, { 5, 4, 4 } };
    int n = sizeof(proc) / sizeof(proc[0]);

    calculateAndDisplayAverageTimes(proc, n);
    return 0;
}
