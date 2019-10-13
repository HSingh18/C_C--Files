#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <semaphore.h>

sem_t s1;		//semaphore for customers
sem_t s2;		//semaphore for increment max_people and printing the message
int max_people = 0;		//max amount of people allowed in the gallery

void *art_gallery(void *k){		//this is the art_gallery
	sem_wait(&s1);		//locking the gallery if too many customers come in
	int i = (int)k;
	sem_wait(&s2);		//locking the value of max_people and print the message
	max_people++;		//when a customer enters the gallery, increment max_people by 1
	printf("Customer #%d: I'm in! (current-customers-in: %d)\n", i, max_people);
	sem_post(&s2);		//unlock the semaphore so that max_people can be updated and the new message can be printed
	usleep(rand()%500000);		//sleep for a random amount of time
	sem_wait(&s2);		//locking the value of max_people and print the message
	max_people--;		//when a customer leaves the gallery, decrement max_people by 1
	printf("Customer #%d: Left! (current-customers-in: %d)\n", i, max_people);
	sem_post(&s2);		//unlock the semaphore so that max_people can be updated and the new message can be printed
	sem_post(&s1);		//unlock the gallery if there is space available
	return NULL;
}

int main(int argc, char *argv[]){
	int customer_number;
	int max_customers;
	if(argv[1] == NULL){
		printf("You forgot to provide a number for max_customers. Quitting\n");
		exit(0);
	}
	if(argv[2] == NULL){
		printf("You forgot to provide a customer number. Quitting\n");
		exit(0);
	}
	else{
		customer_number = atoi(argv[2]);	//second input from user is the number of customers that are going to enter the gallery
		max_customers = atoi(argv[1]);		//first input from user is the max customers allowed into the gallery
	}
	sem_init(&s1, 0, max_customers);		//initialize the semaphore
	sem_init(&s2, 0, 1);					//initialize the semaphore
	pthread_t tid[customer_number];			//create as many threads as there are customers
	int i;
	for(i = 0; i < customer_number; i++){		
		pthread_create(&(tid[i]), NULL, &art_gallery, (void*)i);		//create a thread which links to function art_gallery and passes the customer number
	}
	for(i = 0; i < customer_number; i++){
		pthread_join(tid[i], NULL);
	}
	sem_destroy(&s1);		//destroy the semaphore
	sem_destroy(&s2);		//destroy the semaphore
	if(max_people == 0){	//if the message CLOSED if there is no one in the gallery
		printf("CLOSED\n");
	}
pthread_exit(NULL);
return 0;
}

