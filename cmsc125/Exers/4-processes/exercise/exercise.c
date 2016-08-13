/*
 * Ferriel Lisandro B. Melarpis 
 * 2012-01065
 * CAS BS Computer Science
 * CMSC 125 ST-8L
 * exercise.c 
 * A simple shell program implemented by using processes
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX_LINE 80

/** 
	setup() reads in the next command line, separating it into distinct 
	tokens using whitespace as delimiters. 

	setup() modifies the 'args' parameter so that it holds pointers to 
	the null-terminated strings that are the 'tokens' in the most recent 
	user command line as well as a NULL pointer, indicating the end of 
	the argument list, which comes after the string pointers that have 
	been assigned to args.
	
	EXAMPLE: char * args[] = {"token1", "token2", "token3", NULL};
*/

void setup(char inputBuffer[], char *args[], int *background){
	inputBuffer[0] = 0x0; /* initialize buffer */
    fgets(inputBuffer, MAX_LINE, stdin); /* scan user input */
    if(inputBuffer[0] == 0x0) { putchar('\n'); exit(1); } /* CTRL-D is caught by testing if the input is of lenght 0 */
	int index = 0;
	args[index] = strtok(inputBuffer, " \n"); /* tokenize the string input */
	while(args[index] != NULL) { /* store all the tokens */
		if(strcmp(args[index], "&") == 0) { /* if the last token is & */
			*background = 1; /* set the background flag to 1 */
			args[index] = NULL; /* set the last token to NULL to end the command tokens */
			break; 
		}
		args[++index] = strtok(NULL, " \n"); /* get the next token */
	}
}
// main
int main(void){
	char inputBuffer[MAX_LINE];	/* buffer to hold command entered */
	int background;			/* equal to 1 if a comand is followed by '&' */
	char *args[MAX_LINE/2 + 1]; 	/* command line arguments */
	pid_t pid; /* process id of the child process */
	int status; /* status of the forked child process */
	while (1){
		background = 0;
		printf("\n\x1b[32mMelarpis@ST8L:~$ \x1b[0m");
		/** setup() calls exit() when Control-D is entered */
		setup(inputBuffer, args, &background);
		/** the steps are:
			(1) fork a child process using fork()
			(2) the child process will invoke execvp()
			(3) if background == 1, the parent will wait, 
			    otherwise it will invoke the setup() function again.
		*/
		if((pid = fork()) < 0) { /* fork() failed to create new process */
			fprintf(stderr, "\x1b[31m*** \x1b[0m\x1b[7mERROR: Failed to create child process\x1b[0m\n");
			exit(-1);
		} else if(pid == 0) { /* this is the child process */
			if(execvp(args[0], args) == -1) { /* replace the child process with a shell command */
				fprintf(stderr, "\x1b[31m***\x1b[7mERROR\x1b[0m\x1b[31m: command not found\x1b[0m\n");
				exit(-1);
			}
		} else { /* this is the parent process */
			if(!background) waitpid(pid, &status, 0); /*if the command will run in foreground
				wait till it finished. Else continue to the main loop and fork a new process for 
				the new command to be entered. */
		}
	}
}

