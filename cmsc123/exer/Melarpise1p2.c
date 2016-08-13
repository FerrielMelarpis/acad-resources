/*
 (C)Ferriel Lisandro B. Melarpis
 2012-01065
 CD-2L
 Exercise 1 Part 2
 */

//libraries
#include <stdio.h> // library for input output functions
#include <stdlib.h> // library for memory allocation functions
//Color Definitions ASCII Code
#define RED "\e[31m"
#define GRN "\e[32m"
#define YEL "\e[33m"
#define BLU "\e[34m"
#define MAG "\e[35m"
//STYLE
#define BLD "\e[1m"
#define ITA "\e[3m"
#define BLK "\e[5m"
#define UND "\e[4m"
#define CLR "\e[m"
//Background Color
#define BRED "\e[41m"
#define BGRN "\e[42m"
#define BYEL "\e[43m"
#define BBLU "\e[44m"
#define BMAG "\e[45m" 

typedef struct node_tag{
  int x;
  struct node_tag *next;
} Node;

Node *createNode(){
  Node *n = malloc(sizeof(Node));
  n->next=NULL;
  return n;
}

// function that prints menu
int printMenu(){
	int choice;
	puts(GRN BLD UND BLK"**MENU**"CLR);
	puts(BLU"[1]"ITA"Insert"CLR);
	puts(RED"[2]"ITA"Delete"CLR);
	puts(YEL"[3]"ITA"Print"CLR);
	puts(RED"[4]"ITA"Exit"CLR);
	printf(BBLU BLD GRN"Enter Choice: "CLR);
	scanf("%d", &choice);
	return choice;
}
// function that prints the list
void printList(Node *head){
  Node *tmp = head->next;
  if(!tmp){
    puts(BRED BLD"List is empty."CLR);
    return;
  }
  puts(MAG ITA"LIST:"CLR);
  while(tmp){
    printf(GRN UND"%3d"CLR, tmp->x);
    tmp = tmp->next;
  }putchar('\n');
}
// function that inserts node in the end of the list
void insert(Node *head, Node **tail){
  printList(head);
  Node *newNode = createNode();
  printf(BYEL BLU BLD"Enter number: "CLR);
  scanf("%d", &newNode->x);
  (*tail)->next = newNode;
  (*tail) = (*tail)->next;
  printList(head);
}
// function that deletes node at the beginning of the list
void delete(Node *head, Node **tail){
  printList(head);
  Node *tmp;
  if(head->next==NULL){
    puts(BRED BLD"List is empty."CLR);
    return;
  }
  tmp = head->next;
  
  head->next = head->next->next;
  if(tmp->next==NULL){
    *tail = head;
  }
  free(tmp);
  printList(head);
}
// function for deallocation and exiting program
void terminate(Node *head){
	if(head->next == NULL){
		free(head);
		return;
	}
	Node *tmp;
	while(head->next!=NULL){
		tmp = head;
		head = head->next;
		free(tmp);
	}free(head);
}
// main
int main(void){
  Node *head = createNode();
  Node *tail = head;
  int choice;
    do{
    choice = printMenu();
      switch(choice){
      case 1:insert(head, &tail);break;
      case 2:delete(head, &tail);break;
      case 3:printList(head);break;
      case 4:terminate(head);break;
      default: puts(RED"Invalid Choice!"CLR); break;
      }
    }while(choice!=4);
  return 0;
}
// end of program