/*(c)Ferriel Lisandro B. Melarpis
     CMSC 21 UV-5L
     CAS BSCS
     University of the Philippines Los Banos
*/


//libraries
#include <stdio.h>
#include <stdlib.h>
//node structure
typedef struct nodetag{
  int x;
  struct nodetag *next;
}Node;
// function that prints menu continuously unless you enter 0;
int menu(void){
  int choice;
  do{
    printf("*******MENU********\n");
    printf("[1] Insert at Head\n");
    printf("[2] Insert at Middle\n");
    printf("[3] Insert at Tail\n");
    printf("[0] Exit\n");
    printf("*******************\n");
    printf("Choice: ");
    scanf("%d", &choice);
  }while(choice<0 || choice>3);
  return choice;
}
//function that prints all the value in the linklist
void printList(Node *head){
  //(head->next != NULL)? printf("%2d", head->x), head = head->next, printList(head) : printf("\n"); 
  // the above code can only be used before deallocation so we must change it to more readable and valid even after the allocation
  //to test if the linked list is cleared already
  Node *temp=head;
  if(!temp){// if the list does not contain any value then there's nothing to be printed; 
    return;
  }else{// if the list contains values...
  while(temp->next!=NULL){// traverse the list and print all the value up to the last node
    printf("%d ", temp->x);
    temp=temp->next;
  }
  printf("\n");
  }
}
// function that lets you insert a node at the end of the list
void end(Node **tail, int val){
  (*tail)->x = val;
  (*tail)->next = malloc(sizeof(Node));
  (*tail) = (*tail)->next;
  (*tail)->next = NULL;
}
//function that counts all the nodes in the list
int counter(Node *head){
  int count=0; 
  while(head->next != NULL){
    head = head->next;
    count++;
  }
  return count;
}
// function that lets you insert at the middle of the list(after 4)
void middle(Node *head, int val){
  int n = counter(head), i;
  Node *prev = malloc(sizeof(Node));
  for(i=0;i<n;i++){
    head = head->x == 4? head: head->next;// search for the first occurence of node that contains the value 4.
  }
  prev->next = head->next;
  prev->x = val;
  head->next = prev;
}
// function that lets you insert at the beginning of the list
void begin(Node **head, int val){
  Node *temp = malloc(sizeof(Node));
  temp->x = val;
  temp->next = *head;
  *head = temp;
}
// function that deallocates(deletes) all the nodes
void deallocate(Node **head){
  Node *temp;
  while((*head) != NULL){
    temp = (*head);
    (*head) = (*head)->next;
    free(temp);
  }
}
// This is the main, actually it's the most important part LOL the program cannot run unless you have it
// C program must have at least one function called main LOL echos lang ma'am xD
int main(){
  Node *head, *tail, *p;// pointer declaration - basta yan tawag ko jan XD
  int choice, val;
  p = malloc(sizeof(Node));// allocating - hmm tingin ko gagana pa rin ung code kahit di mo itype cast ung malloc
  // since pointer din naman talaga ung nirereturn :P
  head = p;
  tail = p;
  //initial values in the list
  end(&tail, 5);
  end(&tail, 4);
  end(&tail, 3);
  do{
    choice = menu();
    switch(choice){
      case 1: // insert at head
	printf("Value to be inserted : "); 
	scanf("%d", &val);
	begin(&head, val); 
	printList(head);
	break;
      case 2: // insert after the first occurence of 4
	printf("Value to be inserted : "); 
	scanf("%d", &val);
	middle(head, val); 
	printList(head);
	break; 
      case 3: // insert at the end of the list
	printf("Value to be inserted : "); 
	scanf("%d", &val);
	end(&tail, val); 
	printList(head);
	break;
    }
  }while(choice != 0);
  printList(head);// prints all the values after you exit
  deallocate(&head);// deallocate
  printList(head);// prints nothing
  return 0;
}// tapos na ung program ayun exer8 naman LOL kakain na lang muna kami ma'am xD