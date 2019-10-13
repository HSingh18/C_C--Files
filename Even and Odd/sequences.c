#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

int NUMBER = 20;		//print out the even and odd numbers until NUMBER
pthread_t t1;			//even thread
pthread_t t2;			//odd thread

void *print_sequence(void *p){		//thread function which prints the even or odd number
	if((int)p == 0){		//if p is equal to 0 then print out all even numbers until NUMBER
		int temp = (int)p;
		while(temp <= NUMBER){
			usleep(rand()% 1000000);
			printf("Thread Even: %d\n", temp);
			temp = temp + 2;		//increase temp by 2 because 0+2=2+2=4+2=6
		}
	}
	else{		//if p is not 0 then print out all odd numbers
		int temp = (int)p;
		while(temp <= NUMBER){
			usleep(rand()% 1000000);
			printf("Thread Odd: %d\n", temp);
			temp = temp + 2;		//increase temp by 2 because 1+2=3+2=5+2=7
		}
	}
	return NULL;
}

int main(int argc, char *argv[]){
	if(argv[1] == NULL){		//if user does not give any input, close the program
		printf("You forgot to give a number. Quitting\n");
		exit(0);
	}
	else{
		int temp = atoi(argv[1]);		//set temp to the user input
		NUMBER = temp;		//set temp to global variable NUMBER
	}
	printf("Number: %d\n", NUMBER);
	int i = 0;
	int err;
	err = pthread_create(&t1, NULL, &print_sequence, (void*)i);		//create a thread which links to function print_sequence and pass the number 0 thru it
	if(err != 0){
		printf("error: %s\n", strerror(err));
	}
	err = pthread_create(&t2, NULL, &print_sequence, (void*)i+1);	//create a thread which links to function print_sequence and pass the number 1 thru it	
	if(err != 0){
		printf("error: %s\n", strerror(err));
	}
pthread_exit(NULL);		//exit all threads
return 0;
}
