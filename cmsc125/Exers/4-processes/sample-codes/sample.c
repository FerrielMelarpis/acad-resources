#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

/* 
	This program illustrates the use of control primitives:
 	fork(), exec(), and wait().

	NOTE:
	wait() and waitpid() may not work properly if they are 
	within the same control block as exec()
*/
 

int main()
{
	pid_t pid1, pidCheck; 
	int i, flag = 0;

	// Child process
	if( (pid1 = fork()) < 0)
		printf("Error");

	do{
		// Check if pid1 contains the process id of the child
		// flag check: in this case, exec() should only be done once
		if(pid1 == 0 && flag == 0)
		{
			i = execlp("ls","ls", 0); // exec() the ls command
			flag = 1;
			
		}
		else
		{
			// Wait for the executed command to finish
			// wait() will return the process id if successful
			pidCheck = wait(0);
			// pidCheck = waitpid(pid1, NULL, 0);
		}
	
	
	}while( pidCheck != pid1 );

}
