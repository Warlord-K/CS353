#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<bits/stdc++.h>
using namespace std;

vector<int> data = {1,3,4,6,7,8,10,12};
int thread_num = 0;
int NUM_THREADS = 4;
vector<int> sum(NUM_THREADS);
void * workerThread(void * tid){
    // cout << data.size() << endl;
    // int sum = 0;
    int n = thread_num++;
    for(int i = (n)*(data.size()/NUM_THREADS); i < (n+1)*(data.size()/NUM_THREADS); i++){
        sum[n]+=data[i];
        // cout << n  << " " << i  << " " << data[i] << endl;
    }
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
    int ans = 0;
    for(int i = 0; i < NUM_THREADS; i++){
        // cout << sum[i] << endl;
        ans+=sum[i];
    }
    cout << ans << endl;
    return 0;

}