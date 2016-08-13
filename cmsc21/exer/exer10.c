/**
 *Ferriel Lisandro B. Melarpis
 *CMSC 21 UV-5L
 *2012-01065
 *A program that implements a phone directory using circular doubly linked list 
 */


//libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// structure for the node(contact)
typedef struct nodetag {
  long long int num;
  char name[20];
  struct nodetag *prev;
  struct nodetag *next;
} Node;

// function that allocates memory for the node
Node * createNode() {
  return malloc(sizeof(Node));
}
// function that appends the contact in the list
void insert(Node *head) {
  Node *newNode = createNode();
  newNode->prev = newNode;
  newNode->next = newNode;
  system("clear"); // clears the terminal
  printf("-INSERT--------------------\n");
  printf("|Name: ");
  scanf("%[^\n]", newNode->name);
  while(getchar() != '\n'); // debug
  printf("|Mobile Number: ");
  scanf("%lli", &(newNode->num));
  while(getchar() != '\n'); // debug
  // linking
  newNode->prev=head->prev;
  newNode->next=head;
  head->prev->next=newNode;
  head->prev=newNode;
  printf("|Contact Added!\n");
  printf("---------------------------\n");
  printf("Press Enter to go back to menu...\n");
  while(getchar() != '\n'); // scans until enter key is hit
}
// function that deallocates all the memory used by the nodes
void deallocate(Node *head) {
  Node *p = head->next;
  // if list contains 3 or more
  while(p != head) {
    if(p->prev != head) 
      free(p->prev);
    p = p->next;
  }
  // if list contains less than 2
  if(p != head)
    free(p);
  // base | if list contains one 
  free(head);
}
// prints the list of name of the contacts
void printAll(Node *head) {
  Node *p = head->next;
  int i = 1;
  printf("|Names:\n");
  while(p != head){
      printf("[%d] %s\n", i, p->name);
      p = p->next;
      i++;
  }
  printf("\n");
}
// function that deletes a contact
void delete(Node *head) {
  char name[20];
  Node *p = head->next;
  if(p == head) {
    printf("Nothing to be deleted!\n");
    printf("---------------------------\n");
    printf("Press Enter to go back to menu...\n");
    while(getchar() != '\n');
    return;
  }
  printf("-DELETE--------------------\n");
  printAll(head);
  printf("|Name of Contact: ");
  scanf("%[^\n]", name);
  while(getchar() != '\n');
  p = head->next;
  while(p != head){
    if(strcmp(p->name,name) == 0) {
      p->next->prev = p->prev;
      p->prev->next = p->next;
      free(p);
      printf("|Node deleted!\n");
      printf("---------------------------\n");
      printf("Press Enter to go back to menu...\n");
      while(getchar() != '\n');
      return;
    }
    p = p->next;
  }
  // if the loop breaks and contacts in the list does not match the name
  printf("|Node not found.\n");
  printf("---------------------------\n");
  printf("Press Enter to go back to menu...\n");
  while(getchar() != '\n'); // scans until enter key is hit
}
// function that views the list one by one starting from the first contact appended
void view(Node *head) {
  Node *p = head->next;
  int choice = 4;
  while(choice != 3) {
    system("clear");
    printf("-VIEW----------------------\n");
    printf("|Name: %s\n", p->name);
    printf("|Mobile Number: %lli\n", p->num);
    printf("---------------------------\n");
    printf("%s%s%s%s",
	  "| << [1] Previous [2] Next >>\n", //constchar
	  "| [3] Back to MENU\n", // constchar
	  "| [0] Exit\n", // constchar
	  "Choice: "); // constchar
    scanf("%d", &choice);
    while(getchar() != '\n'); // debug
    switch(choice) {
      case 0 :
	system("clear");
	printf("Exit!\n");
	deallocate(head); // deallocate
	exit(0); // exit
	break;
      case 1 :
	p = p->prev == head? p->prev : p; // if p is equal to the dummyNode head
	p = p->prev;
	break;
      case 2 :
	p = p->next == head? p->next : p; // if p is equal to the dummyNode head
	p = p->next;
	break;
      case 3 : 
	break;
      default : // if choice is greater than 3 or choice < 0
	printf("Invalid\n");
	break;
    }
  }
}

void menu(Node *head) {
  int choice;
  system("clear");
  printf("%s%s%s%s%s%s%s",
	 "********MENU**********\n", // constchar
	 "[1] Insert Contact\n", // constchar
         "[2] Delete Contact\n", // constchar
         "[3] View Contacts\n", // constchar
         "[0] Exit\n", // constchar
         "**********************\n", // constchar
         "Choice: "); // constchar
  scanf("%d",&choice);
  while(getchar() != '\n'); // debug
  switch(choice) {
    case 0 : 
      system("clear"); // clears the terminal
      printf("Exit!\n");
      deallocate(head); // deallocate
      exit(0); // exit
      break;
    case 1 : 
      system("clear"); // clears the terminal
      insert(head); // calls insert function
      break;
    case 2 : 
      system("clear"); // clears the terminal
      delete(head); // calls delete function
      break;
    case 3 : 
      system("clear"); // clears the terminal
      view(head); // calls view function
      break;
    default :
      system("clear"); // clears the terminal
      printf("Invalid!\n");
      break;
    }
  menu(head);
}
 // main
int main(void) {
  // dummy node
  Node *head = createNode();
  head->prev = head;
  head->next = head;
  // menu
  menu(head);
  // deallocate
  deallocate(head);
  // view for testing the deallocation
  view(head);
  return 0; // when program is successful
}