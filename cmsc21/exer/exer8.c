/*
 *Ferriel Lisandro B. Melarpis
 *CMSC 21 UV-5L
 *2012-01065
 *CAS BSCS
 *University of the Philippines Los Banos 
 */
// libraries for standard input, output and memory allocation
#include <stdio.h>
#include <stdlib.h>

// structure for node
typedef struct nodetag{
  int x;
  struct nodetag *next;
} Node;
// function that prints menu until choice = 1 || 2 || 0
int menu(){
  int choice;
  do{
  printf("-----------------M--E--N--U-----------------\n");
  printf("           [1] Insert a node\n");
  printf("           [2] Delete a node\n");
  printf("           [0] Exit\n");
  printf("--------------------------------------------\n");
  printf("Enter your choice : ");
  scanf("%d", &choice);
  if(choice < 0 || choice > 2){
    printf("Invalid Input\n");
  }
  }while(choice < 0 || choice > 2);
  return choice;
}
// function that lets you view all the nodes in the linked list
void view(Node *h){
  Node *p;
  p = h;
  while(p){
    printf("%d ", p->x);
    p = p->next;
  }printf("\n");
}
// function that lets you insert a node and sort the list in ascending order automatically
void insertNode(Node **h, int val){
  Node *newNode = malloc(sizeof(Node));
  Node *p;
  newNode->x = val;
  newNode->next = NULL;
  if(!(*h)){// if the list is empty
    *h = newNode;
  }else if((*h)->x > newNode->x){// if the node is to be inserted in the head
    newNode->next = *h;
    *h = newNode;
  }else{// if the list has at least 1 node and the node to be inserted is somewhere in middle or end
    p = *h;
    while((p->next) && newNode->x > p->next->x){// search for the position of the node to be inserted
      p = p->next;
    }
    newNode->next = p->next;
    p->next = newNode;
  }
}
// function that lets you delete the first occurence of a node in the list
void deleteNode(Node **h, int val){
  Node *temp, *p;
  int c = 0;
  p = *h;
  if(!p){// if the list is empty, there's nothing to delete
    printf("Nothing to be deleted.\n");
  }else{// if the list contains at least one node
    while(p){// traverse the list
      if(p->x == val){// if the node to be deleted is in the list
	if(p == *h){// if the node to be deleted is in the head
	  *h = p->next;// point the head to the next node
	  free(p);//delete the previous head
	  return;// return to main
	}else{// if the node to be deleted is not in the head
	  // this condition can only be satisfied when the node pointer already traverse to other node
	  temp->next = p->next;/*
	  the next pointer of the previous node before the node to be deleted will point to the node after the node to be deleted
	  */ 
	  free(p);// delete the node
	  return;// return to main
	}
	c++;// increments when there is  deleted node
      }else{// if head or the current node is not the node to be deleted
	temp = p;// points to the previous node 
	p = p->next;// then traverse to the next one
      }
    }
    if(c == 0){// if the node to be deleted does not exist in the list
      printf("Not in the list!  ");
    }
  }
}
// main
int main(){
  Node *head = NULL; // empty list
  int val, choice;
  // loop will continue until the user hits zero
  do{
  choice = menu();
    switch(choice){
      case 1://insert
	printf("Enter value to insert : ");
	scanf("%d", &val);
	insertNode(&head, val);
	view(head);// view the list after inserting
	break;
      case 2://delete
	printf("Enter value to be deleted : ");
	scanf("%d", &val);
	deleteNode(&head, val);
	view(head);// view the list after deleting
	break;
      case 0://exit
	printf("Exit!\n");
	break;
    }
  }while(choice != 0);
  
  return 0;// returns 0 if the program is successful
}