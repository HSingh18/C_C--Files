#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char *argv[]) {
	int child_b;		//the child of Process A and the parent of noone
	int child_c;		//the child of Process A and the parent of child_d and child_e
	int child_d;		//the child of child_c and the parent of child_f
	int child_e;		//the child of child_c and the parent of noone
	int child_f;		//the child of child_d and the parent of noone
	int children = 0;	//counter for how many children each child has

	printf("Process A: Pid: %d, Parent: %d\n", getpid(), getppid());
	child_b = fork();		//create a child in Process A
	if (child_b == 0) {		//code for child_b
		printf("Child B: Pid: %d, Parent: %d\n", getpid(), getppid());
		children = 0;
		printf("Child B: Pid: %d, Parent: %d, Children: %d\n", getpid(), getppid(), children);
		exit(0);
	}
	else {		//if you are not in child_b, then you are in Process A
		wait(0);
		children++;
		child_c = fork();		//create a child in Process A
		if (child_c == 0) {		//code for child_c
			printf("Child C: Pid: %d, Parent: %d\n", getpid(), getppid());
			children = 0;
			child_d = fork();		//create a child in child_c
			if (child_d == 0) {		//code for child_d
				printf("Child D: Pid: %d, Parent: %d\n", getpid(), getppid());
				children = 0;
				child_f = fork();		//create a child in child_d
				if (child_f == 0) {		//code for child_f
					printf("Child F: Pid: %d, Parent: %d\n", getpid(), getppid());
					children = 0;
					printf("Child F: Pid: %d, Parent: %d, Children: %d\n", getpid(), getppid(), children);
					exit(0);
				}
				else {		//if you are not in child_f, then you are in child_d
					children++;
				}
				wait(0);
				printf("Child D: Pid: %d, Parent: %d, Children: %d\n", getpid(), getppid(), children);
				exit(0);
			}
			else {		//if you are not in child_d, then you are in child_c
				children++;
			}
			wait(0);
			child_e = fork();		//create a child in child_c
			if (child_e == 0) {		//code for child_e
				printf("Child E: Pid: %d, Parent: %d\n", getpid(), getppid());
				children = 0;
				printf("Child E: Pid: %d, Parent: %d, Children: %d\n", getpid(), getppid(), children);
				exit(0);
			}
			else {		//if you are not in child_e, then you are in child_c
				children++;
			}
			wait(0);
			printf("Child C: Pid: %d, Parent: %d, Children: %d\n", getpid(), getppid(), children);
			exit(0);
		}
		else {		//if you are not in child_c then you are in Process A
			children++;
		}
	}
	wait(0);
	printf("Process A: Pid: %d, Parent: %d, Children: %d\n", getpid(), getppid(), children);
	return 0;
}