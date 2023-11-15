#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#define MAX 100

struct mesg_buffer {
	long n;
} message;

int fib(int n){
	if(n < 3) return n;
	return fib(n-1) + fib(n-2);
}
int main(){
	key_t key;
	int msgid;
	key = ftok("progfile", 65);
	msgid = msgget(key, 0666|IPC_CREAT);	
	msgrcv(msgid, &message, sizeof(message), 0);
	message.n = fib(message.n);
	msgsnd(msgid, &message, sizeof(message), 0);
	msgctl(msgid, IPC_RMID, NULL);
	return 0;
}
