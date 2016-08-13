/* Ferriel Lisandro B. Melarpis
 * 2012-01065
 * CAS BSCS
 * CMSC 125 ST-8L
 * This program implements a Round-Robin (RR) CPU Scheduler. 
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
const int quantum_time = 2;
int q = 0;

void PrintPCB(PCB pcb)
{
	printf("\tProcess ID: %d, Arrival Time: %d, Job Length: %d\n", pcb.process_id, pcb.arrival_time, pcb.job_length);
}

void PrintReadyQueue()
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

void Dequeue()
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

void Processing()
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
    q = 0;
		Dequeue();
	}
	
}

void EnqueueProcess(int arrival, int job_length)
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
		/*traverse the link list to find the tail */
		ptr = ready_queue;
		
		while(ptr->next != NULL)
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
		temp->next = NULL;
		ptr->next = temp;
	}
	process_count++;
}

void RunSimulation()
{
	int index2 = 0;
	cpu_cycles = 1;
  q = 0;
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
    if(++q == quantum_time) /* if quantum time is consumed */
    {
      q = 0;
      if(ready_queue->next != NULL)
      {
       linked_list tail = ready_queue;
       while(tail->next != NULL) /* traverse to the end */
       {
        tail = tail->next;
       }
      /* put the head of the ready queue to the tail and proceed with the next job */
      linked_list temp = ready_queue;
      tail->next = temp;
      ready_queue = ready_queue->next;
      temp->next = NULL;
      }
    }
		if(ready_queue == NULL) break;
	}
}

void ReadFile()
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

int main()
{	
	/*Initialize required variables */
	ready_queue = NULL;
	process_count = 0;
	ReadFile();
	RunSimulation();
  return 0;
}
