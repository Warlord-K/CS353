#include<bits/stdc++.h>
using namespace std;

int main(){
    int n = 5;
    int pid[n];
    int a[n];
    int b[n];
    int t = 4;
    int currentTime = 0;
    int finished = 0;
    int started = 0;
    vector<int> ans;
    cout << "Enter PIDs" << endl;
    for(int i = 0; i < n; i++){
        cin >> pid[i];
    }
    // cout << "Enter Arrival Times" << endl;
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    // cout << "Enter Birst Times" << endl;
    for(int i = 0; i < n; i++){
        cin >> b[i];
    }
    queue<int> q;
    while(finished < n){
        // cout << currentTime << " " << finished << endl;
        while(started < n && a[started] <= currentTime){
            q.push(started);
            started++;
        }
        if(q.empty()){
            ans.push_back(-1);
            currentTime++;
            continue;
        }
        int curr = q.front();
        q.pop();
        cout << 5;
        for(int i = 0; i < min(b[curr],t); i++){
            b[curr]--;
            ans.push_back(pid[curr]);
        }
        if(b[curr] > 0) q.push(curr);
        else finished++;
        currentTime++;
    }
    cout << "Gantt Chart" << endl;
    for(auto i: ans) cout << i << " ";
    cout << endl;
    // cout << ans.size() << endl;
    return 0;
}