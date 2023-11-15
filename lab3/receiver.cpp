#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<bits/stdc++.h>
#include<unistd.h>
#define MAX 100
using namespace std;
struct mesg_buffer {
	long mesg_type;
	int n[5];
} message;

int fib(int n){
	if(n ==1) return 0;
	if(n ==2) return 1;
	return fib(n-1) + fib(n-2);
}
int main(){
	key_t key;
	int msgid;
	key = 80;
	msgid = msgget(key, 0666|IPC_CREAT);
	// cout << errno;
	// cout << key << " " << msgid << endl;
	msgrcv(msgid, &message, sizeof(message),1, 0);
	cout << "Recieved: " << message.n[0] << endl;
	message.mesg_type = 1;
	message.n[0] = fib(message.n[0]);
	cout << message.n[0] << endl;
	msgsnd(msgid, &message, sizeof(message), 0);
	cout << "Sent Answer" << endl;
	msgctl(msgid, IPC_RMID, NULL);
	return 0;
}
