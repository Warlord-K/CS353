#include<bits/stdc++.h>

using namespace std;

int main(){
    // Get the Number of Processes and Resources
    int n, m;
    cout << "Enter Number of Processes: \n";
    cin >> n;
    cout << "Enter Number of Resources: \n";
    cin >> m;
    // Make the Required Matrices
    int available[m];
    int max[n][m];
    int allocated[n][m];
    int need[n][m];
    // Get the Input Data
    cout << "Enter Available Resources(Separated by space): \n";
    for(int i=0; i<m; i++){
        cin >> available[i];
    }
    cout << "Enter Max Resources(Separated by space): \n";
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin >> max[i][j];
        }
    }
    cout << "Enter Allocated Resources(Separated by space): \n";
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin >> allocated[i][j];
        }
    }
    // Calculate the Need Matrix
    cout << "Need matrix: \n";
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            need[i][j] = max[i][j] - allocated[i][j];
            cout << need[i][j] << " ";
        }
        cout << endl;
    } 
    bool finish[n] = {false};
    int safe[n];
    int count = 0;
    // The Algorithm runs till all processes are safe or No process is found to be safe in the current iteration
    while(count < n){
        bool found = false;
        for(int i=0; i<n; i++){
            // If process not finished
            if(finish[i] == false){
                int j;
                // Find the resource which is not available
                for(j=0; j<m; j++){
                    if(need[i][j] > available[j]){
                        break;
                    }
                }
                // If all resources are available
                if(j == m){
                    // Add to available, since the allocated resources will be free eventually
                    for(int k=0; k<m; k++){
                        available[k] += allocated[i][k];
                    }
                    // Add Process ID to Safe Array
                    safe[count++] = i;
                    // Mark as done
                    finish[i] = true;
                    // Go to next iteration
                    found = true;
                }
            }
        }
        // If no process got finished this iteration then System is not safe.
        if(found == false){
            cout << "System is Not Safe!\n";
            return 0;
        }
    }
    // System is Safe
    cout << "System is Safe!\n";
    // Print Safe Sequence
    cout << "Safe sequence: ";
    for(int i=0; i<n; i++){
        cout << "P" << safe[i] << " ";
    }
    cout << endl;
    return 0;
}

/*
Available:
2 1 0 0

Max:
0 0 1 2
2 7 5 0
6 6 5 0
4 3 5 6
0 6 5 2

Allocated:
0 0 1 2 
2 0 0 0
0 0 3 4
2 3 5 4
0 3 3 2
*/