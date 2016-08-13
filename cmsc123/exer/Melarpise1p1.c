/*
	(C) Ferriel Lisandro B. Melarpis
	2012-01065
	CMSC 123 CD-2L
*/
// libraries
#include <stdio.h>
#include <stdlib.h>
// for printing with colors
#define RED "\e[31m"
#define GRN "\e[32m"
#define YEL "\e[33m"
#define BLU "\e[34m"
#define VIO "\e[35m"
#define CYN "\e[36m"

#define CLR "\e[m"
#define BRT "\e[1m"
#define UND "\e[4m"
// structure
typedef struct node_tag{
	int x;
	struct node_tag *next;
}Node;
// prototype
void printList(Node *head);
// function definitions
// function that prints menu
int printMenu(){
	int choice;
	puts(GRN BRT UND"MENU"CLR);
	puts(BLU"[1]Insert"CLR);
	puts(CYN"[2]Delete"CLR);
	puts(YEL"[3]Print"CLR);
	puts(RED"[4]Exit"CLR);
	printf(GRN"Enter Choice: "CLR);
	scanf("%d", &choice);
	return choice;
}
// function that creates Node
Node * createNode(){
	return malloc(sizeof(Node));
}
// function that inserts a node at the beginning of the list
void insert(Node *head){
Node *temp = createNode();
	printList(head);
	printf("Enter number: ");
	scanf("%d", &temp->x);
	if(head->next == NULL){
		head->next = temp;
	}else{
		temp->next = head->next;
		head->next = temp;
	}
	printList(head);
}
// function that displays the list
void printList(Node *head){
Node *temp = head->next;
	if(head->next == NULL){
		puts(RED"List is Empty."CLR);
		return;
	}
	puts(CYN BRT"LIST:"CLR);
	while(temp!=NULL){
		printf(VIO BRT UND "%3d" CLR, temp->x);
		temp = temp->next;
	}printf("\n");
}
// function that deletes a node at the beginning of the list
void delete(Node *head){
	printList(head);
	Node *tmp;
	if(head->next == NULL){
		puts(RED"List is empty"CLR);
		return;
	}else{
		tmp = head->next;
		head->next = head->next->next;
		free(tmp);
	}
	printList(head);
}
// function for deallocation
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
int choice;
	do{
	choice = printMenu();
	switch(choice){
	case 1:insert(head);break;
	case 2:delete(head);break;
	case 3:printList(head);break;
	case 4:terminate(head);break;
	default: puts(RED"Invalid Choice!"CLR); break;
	}
	}while(choice!=4);
	return 0;
}
