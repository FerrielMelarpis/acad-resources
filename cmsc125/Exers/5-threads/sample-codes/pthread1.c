#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print_message_function( void *ptr );

main()
{
	/* Declare 2 threads: 'thread1' and 'thread2' */
     pthread_t thread1, thread2;
     
     /* Function arguments: string messages */
     char *message1 = "Thread 1";
     char *message2 = "Thread 2";
     
	/* Create independent threads. Each of which will execute a function */
	/* pthread_create(&threadID, threadAttrib, function, fxnArguments)   */
	pthread_create( &thread1, NULL, print_message_function, (void*) message1);
     pthread_create( &thread2, NULL, print_message_function, (void*) message2);

     /* 
        Wait till threads are complete before main continues. Unless we  
        wait we run the risk of executing an exit which will terminate   
        the process and all threads before the threads have completed.   */
	/* pthread_join(threadID, &status) */
     pthread_join( thread1, NULL);
     pthread_join( thread2, NULL); 

     /* Thread Termination */
     /* pthread_exit(&resturnStatus) */
	pthread_exit(NULL);
}

/* (void *) - generic pointer */
void *print_message_function( void *ptr ){
     char *message;
     
     /* Typecasting of function argument */
     message = (char *) ptr;
     
     printf("%s \n", message);
     
     /* Thread Termination */
     /* pthread_exit(&resturnStatus) */
     pthread_exit(NULL);
}
