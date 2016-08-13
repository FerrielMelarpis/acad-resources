/**
  *Ferriel Lisandro B. Melarpis
  *2012-01065
  *CAS BSCS
  *CMSC 21 UV-5L
  *Doubly Linked List Program(Without the use of Dummy Nodes)
  *implementing inserting and deleting node
*/
//libraries
#include <stdio.h> // for standard input output functions
#include <stdlib.h> // for memory allocation usage
// structure(NODE)
typedef struct nodetag {
    int x;
    struct nodetag *next;
    struct nodetag *prev;
} Node;
// function that prints the menu until choice = 0 || 1 || 2
int menu() {
    int c;
    do {
        printf("-------------------------------\n");
        printf("[1] Insert a node\n");
        printf("[2] Delete a node\n");
        printf("[0] Exit\n");
        printf("-------------------------------\n");
        printf("Enter your choice\n>> ");
        scanf("%d", &c);
        if(c < 0 || c > 2) {
            printf("Invalid !\n");
        }
    }while(c < 0 || c > 2);
    return c;
}
// function that inserts a node and sorts it in ascending order
void insertNode(Node **h, int val) {
    Node *newNode = malloc(sizeof(Node));
    newNode->x = val;
    newNode->next = newNode->prev = NULL;
    Node *p = *h;
    if(!*h) {// if list is empty
        *h = newNode;
    }else if((*h)->x > newNode->x) { // insert at head
        (*h)->prev = newNode;
        newNode->next = (*h);
        *h = newNode;
    }else{
        while(p->next && newNode->x > p->next->x) {/* traverse until a node is greater than the new node
            or if there is no existing next node*/
            p = p->next;
        }
        if(p->next) { // insert at middle
            newNode->next = p->next;
            newNode->prev = p;
            p->next->prev = newNode;
            p->next = newNode;
        }else{ // insert at tail
            newNode->prev = p;
            p->next = newNode;
        }
    }
}
// function that deletes a certain node
void deleteNode(Node **h, int val) {
    Node *newNode = malloc(sizeof(Node));
    newNode->x = val;
    newNode->next = newNode->prev = NULL;
    Node *temp, *p = *h;
    int c = 0;

    if(!p) { // if the list is empty
        printf("Nothing to be deleted!\n");
    }else{ // if the list contains at least 1 node
        while(p) {// traverse the list
            if(p->x == val) {
                if(p == *h) { // if the node to be deleted is the head
                    if(p->next){ // if the list contains two or more nodes
                        *h = p->next;
                        (*h)->prev = NULL;
                        free(p);
                        return;
                    }else{ // if the list contains only one node
                        *h = NULL;
                        free(p);
                        return;
                    }
                }else if(!p->next) { // if the last node is to be deleted
                    temp->next = NULL;
                    free(p);
                    return;
                }else{ // deleting at the middle
                    temp->next = p->next;
                    p->next->prev = temp;
                    free(p);
                    return;
                }
                c++;// increments when there is a node deleted
            }else{ // if the node to be deleted is not the head
                temp = p; // previous node
                p = p->next; // traverse
            }
        }
        if(c == 0) { // if the node to be deleted does not exist
            printf("Not in the list!\n");
        }
    }
}
// function that prints the linked list in ascending and descending order
void view(Node **h) {
    Node *p = *h;
    if(p){ // if list not empty
        while(p->next) {
            printf("%d ", p->x);
            p = p->next;
        }printf("%d\n", p->x);
        while(p->prev) {
            printf("%d ", p->x);
            p = p->prev;
        }printf("%d\n", p->x);
    }else{ // if list is empty
        printf("List is empty.\n");
    }
}
// function that deallocates all the memory accessed by the nodes
void deallocate(Node **h) {
    Node *p;
    while(*h) {
        p = *h;
        *h = (*h)->next;
        free(p);
    }
}
// main : int
int main() {
    Node *head = NULL;
    int choice, num;
    // loops until choice is 0
    do {
        choice = menu();
        switch(choice) {
        case 0 : // exit
            printf("Exit !\n");
            break;
        case 1 : // insert a node
            printf("Enter number to insert : ");
            scanf("%d", &num);
            insertNode(&head, num);
            view(&head);
            break;
        case 2 :// delete a node
            printf("Enter number to delete : ");
            scanf("%d", &num);
            deleteNode(&head, num);
            view(&head);
            break;
        }
    }while(choice != 0);
    // deallocate
    deallocate(&head);
    // check if memory is successfully deallocated
    view(&head);
    return 0; // returns 0 if the program is successful
}
