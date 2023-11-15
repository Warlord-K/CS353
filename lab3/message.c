#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<bits/stdc++.h>
using namespace std;
#define MAX 100

struct mesg_buffer {
	long n;
} message;


int main(){

	key_t key;
	int msgid;
	
	key = ftok("progfile", 65);
	
	msgid = msgget(key, 0666|IPC_CREAT);
	message.mesg_type = 1;
	cin >> message.n;
	msgsnd(msgid, &message, sizeof(message), 0);
	msgrcv(msgid, &message, sizeof(message), 0);
	cout << message.n << endl;
	msgctl(msgid, IPC_RMID, NULL);
	return 0;
}