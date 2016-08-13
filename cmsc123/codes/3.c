#include <stdio.h>
#include <stdlib.h>

typedef struct node_tag Queue;
typedef struct list_tag Machine;
struct node_tag{
  int x;
  Queue *next;
};
struct list_tag{
  Queue *head;
  Queue *tail;
};

Queue *createQueue(){
  Queue *q = malloc(sizeof(Queue));
  q->next = NULL;
  return q;
}

Machine *createMachine(){
  Machine *m = malloc(sizeof(Machine));
  m->head = m->tail = createQueue();
  return m;
}

void enqueue(Machine *m, int x){
  m->tail->next = createQueue();
  m->tail->next->x = x;
  m->tail = m->tail->next;
}

int dequeue(Machine *m){
  if(m->head->next==NULL){
    return -1;
  }
  Queue *tmp = m->head->next;
  m->head->next = m->head->next->next;
  int x = tmp->x;
  free(tmp);
  return x;
}

int input(Machine *main, Machine ***m){
  FILE *fp=fopen("input.txt","r");
  int x, i;
  if(!fp){
    return -1;
  }else{
    do{
      fscanf(fp,"%d", &x);
      enqueue(main, x);
    }while(fgetc(fp)!='\n');
    fscanf(fp,"%d", &x);
    *m = malloc(sizeof(Machine)*x);
    for(i=0;i<x;i++){
      *(*m+i)=createMachine();
    }
  }
  fclose(fp);
  return x;
}

int getSum(Machine *m){
  int sum=0;
  Queue *tmp = m->head->next;
  while(tmp!=NULL){
    sum+=tmp->x;
    tmp = tmp->next;
  }
  return sum;
}

int getIndex(Machine **m, int x){
  int i, sum, min=10000, index;
  for(i=0;i<x;i++){
    sum = getSum(m[i]);
    if(sum<min){
      min = sum;
      index = i;
    }
  }
  return index;
}

void mOutput(FILE *fp, Machine *m){
  Queue *tmp=m->head->next;
  while(tmp!=NULL){
    fprintf(fp,"%3d",tmp->x);
    tmp=tmp->next;
  }fputc('\n', fp);
}

void output(Machine **m, int size){
  FILE *fp=fopen("output.txt","w");
  int i;
  for(i=0;i<size;i++){
    fprintf(fp,"Machine %d: ", i+1);
    mOutput(fp, m[i]);
  }
  fclose(fp);
}

void terminate(Machine *m){
  Queue *tmp;
  while(m->head->next!=NULL){
    tmp = m->head->next;
    m->head->next = m->head->next->next;
    free(tmp);
  }
  free(m->head);
  free(m);
}

int main(void){
  Machine *main = createMachine();
  Machine **m;
  int n, x, size = input(main, &m);
  if(size==-1){ 
    fprintf(stderr,"FILE NOT FOUND\n");
  }else{
    while((n=dequeue(main))!=-1){
      x = getIndex(m, size);
      enqueue(m[x], n);
    }
    output(m, size);
  }
  int i;
  for(i=0;i<size;i++){
    terminate(m[i]);
  }
  terminate(main);
  return 0;
}