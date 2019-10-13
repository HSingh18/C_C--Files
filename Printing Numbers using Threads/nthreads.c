#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

	char *messages[] = {"Hello\n", "Bonjour\n", "Hola\n", "Sata Sri Akala\n", "Hallo\n", "Aloha\n", "Ciao\n", "Hej\n", "Salve\n", "Halo\n"};		//list of messages to print out

	int NUMBER;		//number that the user passes to the program

void *print_msg(void *num){		//thread fucntion that prints the messages
	usleep(rand()% 1000000);	//random sleep time
	printf("Thread%d: %s", (int)num+1, messages[(int)num]);		//print the thread number and the respective messages
	return NULL;
}

int main(int argc, char *argv[]){		//argv is provided at program execuation
	if(argv[1] == NULL){		//if the user does not provide any input then print all the messages
		printf("You forgot to pass a number. NUMBER = 10\n");
		NUMBER = 10;
	}
	else{		
		int temp;
		temp = atoi(argv[1]);		//set the user input number to temp
		if(temp > 10){		//if the user gives a number greater than 10 then set temp to 10
			printf("You can not go above 10\n");
			temp = 10;
		}
		NUMBER = temp;		//set temp to global variable NUMBER
	}
	printf("NUMBER: %d\n", NUMBER);
	int i = 0;
	pthread_t tid[NUMBER];		//create NUMBER amount of threads
	int err;
	for(i = 0; i < NUMBER; i++){
		err = pthread_create(&(tid[i]), NULL, &print_msg, (void*)i);		//creation of a thread, go into the function print_msg, input is i
		if(err != 0){
			printf("error:%s\n", strerror(err));
		}
pthread_exit(NULL);
return 0;
}

