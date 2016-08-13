#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	pid_t processID, parentID;
	
	processID = getpid();
	printf("\nProcess id is %d\n", processID);

	parentID = getppid();
	printf("Parent Process id is %d\n", parentID);
	
	sleep(5); 

	printf("%d is Awake.\n\n", processID);
	exit(0);
}
