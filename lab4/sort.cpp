#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<bits/stdc++.h>
using namespace std;

vector<int> a = {10, 9, 8,7,6,5,4,3,2,1};
int thread_num = 0;
int NUM_THREADS = 2;
vector<int> sum(NUM_THREADS);
void * workerThread(void * tid){
    // cout << data.size() << endl;
    // int sum = 0;
    int n = thread_num++;
    sort(a.begin() + 5*n, a.begin() + 5*(n+1));
    // pthread_exit(&sum);
    return NULL;
}

int main(){
    pthread_t threads[NUM_THREADS];
    
    for(int i = 0; i < NUM_THREADS; i++){
        pthread_create(&threads[i], NULL, workerThread, (void *) &threads[i]);
    }
    for(int i = 0; i < NUM_THREADS; i++){
        pthread_join(threads[i], NULL);
    }
    vector<int> ans(10);
    merge(a.begin(), a.end() - 5, a.begin() + 5, a.end(), ans.begin());
    for(auto k:ans) cout << k << " ";
    cout << endl;
    return 0;

}