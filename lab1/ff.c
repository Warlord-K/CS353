#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main(int argc, char *argv[]){
	execvp("/usr/bin/firefox", NULL);
	return 0;

}
