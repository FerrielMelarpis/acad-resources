/********************************************************************************************
Author: 
Date: 
Program Description: 
********************************************************************************************/

#include<stdio.h>								//libraries
#include<stdlib.h>

#define MAXGRAPHSIZE 12

typedef struct s{								//stack 
  int stkLimit;
  int top;
  int *stkArray;
}stack;

typedef struct q{								//queue
   int qlimit;
   int head;
   int tail;
   int qsize;
   int *qArray;
}queue;

int menu();										//function prototypes
int readFile(int **graph);
void printMatrix(int **graph, int size);
void dfs(int s, int size);
void bfs(int s, int size);
stack *stkCreate(int size);
void push(int x, stack *s);
int pop(stack *s);
queue *qCreate(int max);
void enqueue(int x, queue *q);
int dequeue(queue *q);

main()											//main program
{
	int **graph;
	int size,choice;
	
	size=readFile(graph);
	
	while((choice=menu())!=3){
		switch(choice){
			case 1:   dfs(0,size);
					  break;
			case 2:   bfs(2,size);	
		}
	}
}

int menu(){
	int choice;
	printf("\n   MENU     ");
	printf("\n[1] - DFS");
	printf("\n[2] - BFS");
	printf("\n[3] - Exit");
	printf("\nYour choice: ");
	scanf("%i",&choice);
	return choice;
}

//************ FILE READING and ADJACENCY MATRIX REPRESENTATION ******************
int readFile(int **graph)										
{
	FILE *fp;
	int i,x,y,size;
	
	//first line of file is the no. of vertices (size of matrix)
	fp = fopen("input.txt","r");
	fscanf(fp,"%i",&size);
	
	//dynamic matrix declaration given the number of vertices
	graph = (int **)malloc(sizeof(int *)*size);
	for(i=0;i<size;i++)
		graph[i] = (int *)malloc(sizeof(int)*size);
	
	//matrix initialization to 0; can be -1 or any other value 
	for(x=0;x<size;x++)
		for(y=0;y<size;y++)	
			graph[x][y]=0;
	
	//per line reading of remaining file data (edges in the graph)
	while(!(feof(fp))){
		fscanf(fp,"%i",&x);
		fscanf(fp,"%i",&y);
		//update matrix here to record graph edges
		________________________
	}	
	
	//displays adjacency matrix on screen
	printMatrix(graph, size);
	
	fclose(fp);	
	return size;
}

void printMatrix(int **graph, int size){
	int i,j;
	
	printf(" ");
	for(i=0;i<size;i++)
		printf(" %i",i);
	printf("\n");	
	for(i=0;i<size;i++){
		printf("%i ",i);
		for(j=0;j<size;j++)	
			printf("%i ",graph[i][j]);
		printf("\n");
	}
}

// **********************	GRAPH TRAVERSAL   *****************************
void dfs(int s, int size) {
 	int j,v, visited[MAXGRAPHSIZE]; stack dfs_stack;
	
	for (j=0; j<size; j++) visited[j]=FALSE;
	push(s,dfs_stack);
	do  {
		v=pop(dfs_stack);
		if (!visited[v])  {
		   visited[v]=TRUE;
		   printf("%d\n",v);
		   for each vertex j adjacent to v
		      if (!visited[j]) push(j,dfs_stack);
		}		  
	} while(!is_empty_stack(dfs_stack)
}


void bfs(int s, int size) {
 	int j,v, visited[MAXGRAPHSIZE]; queue bfs_queue;
	
	for (j=0; j<size; j++) visited[j]=FALSE;
	enqueue(s,bfs_queue);
	do  {
		v=dequeue(bfs_queue);
		if (!visited[v])  {
     		   visited[v]=TRUE;
		   printf("%d\n",v);
		   for each vertex j adjacent to v
		      if (!visited[j]) enqueue(j,bfs_queue);
	        }		  
	} while(!is_empty_queue(bfs_queue)
}

// **********************	STACK OPERATIONS   ***************************
stack *stkCreate(int size){
  stack *stk;
  
  stk = (stack *)malloc(sizeof(stack));
  stk->stkArray = (int *)malloc(sizeof(int)*size);
  stk->top = 0;
  stk->stkLimit = size;
  return stk;
}

void push(int x, stack *s){
  if (s->top < s->stkLimit){ 
    s->stkArray[s->top] = x;
    (s->top)++;
  }
  else {
    printf("stack overflow");
    exit(1);
  }
}

int pop(stack *s){
  if (s->top > 0){ 
   (s->top)--;
   return(s->stkArray[s->top]);
  }
  else {
    printf("stack underflow");
    exit(1);
  }
}

// **********************	QUEUE OPERATIONS   ***************************
queue *qCreate(int max){
  queue *q;
  q = (queue *)malloc(sizeof(queue));
  q->qArray = (int *)malloc(sizeof(int)*max);
  q->head = 1;
  q->tail = 0;
  q->qSize = 0;
  q->qLimit = max;
  return q;
}

void enqueue(int x, queue *q){
  if(q->qSize < q->qLimit){
    q->qSize++;
    q->tail = ((q->tail)+1)%q->qLimit;
    q->qArray[q->tail]=x;
  }
  else {
    printf("queue overflow");
    exit(1);
  }
}

int dequeue(queue *q){
  int x;

  if(q->qSize > 0){
    q->qSize--;
    x = q->qArray[q->head]);
    q->head = ((q->head)+1)%q->qLimit;
    return x;
  }
  else {
    printf("queue underflow");
    exit(1);
  }
}
