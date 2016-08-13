#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid;
	int status, died;

	switch( pid = fork() )
	{
		case -1: perror ("Error in fork");
			 exit(0);

		case 0 : /* Processing for child */
			 printf("\nChild report: my PID = %d; pid (var) = %d\n\n", getpid(), pid);
			 sleep(5);
			 break;

		default: /* Processing for parent */
			 printf("\nParent report: my PID = %d; pid (var) = %d\n", getpid(), pid);
			 died = wait(&status);
	}

	exit(0);
}
