#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	pid_t pid;

	/* Fork another process */
	pid = fork();

	/* Error has occured */
	if (pid < 0){		
		fprintf(stderr, "Fork Failed");
		exit(-1);
	}
	/* Processing for Child */
	else if (pid == 0){	
		printf("\n.....Child process executes.....\n");
		execlp("/bin/ls", "ls", NULL);
	}
	/* Processing for Parent */
	else{
		printf(".....Parent process executes.....\n");

		/* Parent will wait for the child process to complete */
		wait(NULL);

		printf("\n.....Child process terminates.....\n");
		printf("\n.....Parent process terminates.....\n\n");
		exit(0);
	}
}
