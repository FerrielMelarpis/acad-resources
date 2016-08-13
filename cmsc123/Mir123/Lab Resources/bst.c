/********************************************************************************************
Author: Ferriel Lisandro B. Melarpis
Date: 12-04-13
Program Description: Binary Search Tree Implementation
********************************************************************************************/

#include<stdio.h>								//libraries
#include<stdlib.h>

typedef struct node{
  int value;
  struct node *left;
  struct node *right;
  struct node *parent;
}BST;

int menu();
BST *newNode(BST *root, int x);					//prototypes
BST *insertNode(BST *root, BST *temp);
BST *search(BST *root, int x);
BST *findMin(BST *root);
BST *deleteNode(BST *root, int x);
void printBST(BST *root,int tabs);

main()											//main program
{
	BST *root=NULL;
	int x, choice;
	
	while((choice=menu())!=3){
		printf("Value: ");
		scanf("%i",&x);
		switch(choice){
			case 1: root = newNode(root, x);
				printBST(root, 1);
					break;
			case 2:	root = deleteNode(root, x);	
		}
	}
}

int menu(){
	int choice;
	printf("\n   MENU     ");
	printf("\n[1] - Insert");
	printf("\n[2] - Delete");
	printf("\n[3] - Exit");
	printf("\nYour choice: ");
	scanf("%i",&choice);
	return choice;
}

BST *newNode(BST *root, int x){
//creates new node with value x
    BST *tmp=malloc(sizeof(BST));
    tmp->parent=tmp->right=tmp->left=NULL;
    tmp->value=x;
//calls insertNode to add the new node to the BST
    root=insertNode(root, tmp);
    return root;
}

BST *insertNode(BST *root, BST *temp){
//inserts node pointed by temp to the BST
    temp = malloc(sizeof(BST));
    temp->parent=temp->right=temp->left=NULL;
    if(root==NULL)
	root=temp;
    else{
	temp->parent=root;
	if(root>temp)
	    insertNode(root->left, temp);
	else
	    insertNode(root->right, temp);
    }
    return root;
}

BST *deleteNode(BST *root, int x){
//deletes the node with value x
}

BST *search(BST *root, int x){
//returns a pointer to the node with value x
}

BST *findMin(BST *root){
//returns a pointer to the node with the minimum value
}

void printBST(BST *root,int tabs){
//tabs should be equal to the current height of the tree
  int i;
  if(root!=NULL){
  	printBST(root->right,tabs+1);
  	for(i=0;i<tabs;i++) printf("\t");
  	printf("%3i\n",root->value);
  	printBST(root->left,tabs+1);  		
  }  
}