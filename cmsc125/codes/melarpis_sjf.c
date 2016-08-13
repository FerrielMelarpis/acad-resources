/* Ferriel Lisandro B. Melarpis
 * 2012-01065
 * CAS BSCS
 * CMSC 125 ST-8L
 * This program implements a Shortest Job First (SJF) CPU Scheduler. 
 *  Implementation Requirements:
 *   1. Process Control Block (PCB) - description of each process
 *   2. Ready Queue - contains all the processes waiting to be run
*/

#include <stdio.h>
#include <stdlib.h>

/* Process Control Block (PCB) */
typedef struct _PCB
{
	int process_id;
	int arrival_time;
	int job_length;
	int wait_time;
	int run_time;
}PCB;

/* A singly-linked list of PCB */
typedef struct _linked_list
{
	PCB pcb;
	struct _linked_list *next;
}*linked_list;

/* Global Variables */
int process_count;
linked_list ready_queue;
int cpu_cycles;

int arrival_time[256];
int job_length[256];
int index;

PrintPCB(PCB pcb)
{
	printf("\tProcess ID: %d, Arrival Time: %d, Job Length: %d\n", pcb.process_id, pcb.arrival_time, pcb.job_length);
}

PrintReadyQueue()
{
	linked_list ptr;
	ptr = ready_queue;
	printf("\n\tPrinting Ready Queue\n");
	while(ptr!=NULL)
	{
		PrintPCB(ptr->pcb);
		ptr = ptr->next;
	}
}

Dequeue()
{	
	linked_list temp;
	
	/* Dequeue the head of the ready queue */
	printf("\n\t==============================================\n");
	printf("\tProcess %d Finished \n", ready_queue->pcb.process_id);
	printf("\tRun Time: %d \n", ready_queue->pcb.run_time);
	printf("\tWait Time: %d\n\tTurn Around Time: %d\n", ready_queue->pcb.wait_time, ready_queue->pcb.run_time + ready_queue->pcb.wait_time);
	temp = ready_queue;
	ready_queue = ready_queue->next;
	free(temp);
	printf("\t==============================================\n");
}

Processing()
{
	/*This simulates a processing of a single CPU cycle
	The first process in the ready queue will increment its run time
	The other process will increment their wait time. */
	
	/*other process*/
	linked_list ptr;
	
	if(ready_queue == NULL)
	{
		/*There are no ready jobs*/
		return;
	}
	/* The first process in the ready queue will increment its run time. */
	ready_queue->pcb.run_time++;
	
	ptr = ready_queue;
	ptr = ptr->next;
	while(ptr != NULL)
	{
		/* The other process will increment their wait time. */
		ptr->pcb.wait_time++;
		ptr = ptr->next;
	}
	
	/*if run_time == job length, then dequeue the job */
	if(ready_queue->pcb.job_length <= ready_queue->pcb.run_time)
	{
		Dequeue();
	}
	
}

EnqueueProcess(int arrival, int job_length)
{
	linked_list temp;
	linked_list ptr;
	if (ready_queue == NULL)
	{
		/*Create a new process*/
		temp = malloc(sizeof(struct _linked_list));
		temp->pcb.arrival_time = arrival;
		temp->pcb.job_length = job_length;
		temp->pcb.process_id = process_count;
		temp->pcb.run_time = 0;
		temp->pcb.wait_time = 0;
		temp->next = NULL;
		ready_queue = temp;
		
	}
	else
	{
		/*queue is not NULL */
		/*traverse the link list to find the right position for insertion sort */
		ptr = ready_queue;
		while(ptr->next != NULL && ptr->next->pcb.job_length <= job_length)
		{
			ptr = ptr->next;
		}
		/*Create a new process*/
		temp = malloc(sizeof(struct _linked_list));
		temp->pcb.arrival_time = arrival;
		temp->pcb.job_length = job_length;
		temp->pcb.process_id = process_count;
		temp->pcb.run_time = 0;
		temp->pcb.wait_time = 0;
		if(ptr->next == NULL) /* if position is at the tail */
		{
			temp->next = NULL;
			ptr->next = temp;
		}
		else /* somewhere from head up to node before the tail */
		{
			temp->next = ptr->next;
			ptr->next = temp;
		}
	}
	process_count++;
}

RunSimulation()
{
	int index2 = 0;
	cpu_cycles = 1;
	while(1)
	{
		printf("\nCPU Cycle: %d\n", cpu_cycles);
		if (ready_queue != NULL)
			printf("\n\tProcess ID %d Running...\n", ready_queue->pcb.process_id);
		
		if(cpu_cycles == arrival_time[index2])
		{
			/* Add a new process in the ready_queue */
			
			printf("\n\t++++++++++++++++++++++++++++++++++++++++++++++\n");
			printf("\tNew Process Arrived\n\tProcess ID: %d, Job Length: %d\n", process_count, job_length[index2]);
			EnqueueProcess(arrival_time[index2], job_length[index2]);
			PrintReadyQueue();
			printf("\t++++++++++++++++++++++++++++++++++++++++++++++\n");
			index2++;
		}
		
		Processing();
		cpu_cycles++;
		if(ready_queue == NULL) break;
	}
}

ReadFile()
{
	/* To read process.txt, store the processes' data into two global arrays: 'arrival_time' and 'job_length' */
	int arrival, length;
	
	/* Read File process.txt */
	FILE *fp;
	fp = fopen("process.txt", "rw");
	
	/* <process.txt>
	   The format of the process.txt file is :
	   <arrival_time> <job_length>
	
	   The arrival time is already arranged in ascending order.
	   Increment the process ID for each new process.
	   The last entry of the process.txt file is "-1 -1" 
	*/
	index = 0;
	while(!feof(fp))
	{
		fscanf(fp, "%d %d", &arrival, &length);
		arrival_time[index] = arrival;
		job_length[index] = length;
		index++;
	}
	fp = NULL;
}

main()
{	
	/*Initialize required variables */
	ready_queue = NULL;
	process_count = 0;
	ReadFile();
	RunSimulation();
}
