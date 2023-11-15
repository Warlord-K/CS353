#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<bits/stdc++.h>
#include<unistd.h>
#include<errno.h>

using namespace std;
#define MAX 100

struct mesg_buffer {
	long mesg_type;
	int n[5];
} message;


int main(){

	key_t key;
	int msgid;
	key = 80;
	
	msgid = msgget(key, 0666|IPC_CREAT);
	// cout << key << " " << msgid << endl;
	message.mesg_type = 1;
	cout << "Enter Number: ";
	cin >> message.n[0];
	msgsnd(msgid, &message, sizeof(message), 0);
	cout << "Sent" << endl;
	cout << errno;
	msgrcv(msgid, &message, sizeof(message),1, 0);
	cout << message.n[0] << endl;
	msgctl(msgid, IPC_RMID, NULL);
	return 0;
}
