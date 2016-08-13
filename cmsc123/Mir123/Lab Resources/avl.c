/********************************************************************************************
Author: 
Date: 
Program Description: 
********************************************************************************************/

#include<stdio.h>								//libraries
#include<stdlib.h>

typedef struct node{
  int value;
  int height;
  struct node *left;
  struct node *right;
  struct node *parent;
}AVL;

int menu();
AVL *newNode(AVL *root, int x);					//prototypes
AVL *insertNode(AVL *root, AVL *temp);
AVL *search(AVL *root, int x);
AVL *findMin(AVL *root);
AVL *deleteNode(AVL *root, int x);
void printAVL(AVL *root, int tabs);
//add function leftRotate()
//add function rightRotate()
//you may also use a separate function checkBalance()

main()											//main program
{
	AVL *root=NULL;
	int choice=0,x;
	
	while((choice=menu())!=3){
		printf("Value: ");
		scanf("%i",&x);
		switch(choice){
			case 1: root = newNode(root, x);
					  printAVL(root,2);	
					  break;
			case 2: root = deleteNode(root, x);	
					  printAVL(root,2);	
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

//***** NOTE: UPDATE HEIGHTS OF AFFECTED NODES AFTER INSERTION *****
//***** ROTATE WHEN NECESSARY *****

AVL *newNode(AVL *root, int x){
//creates new node with value x
	AVL *temp;

	temp=(AVL *)malloc(sizeof(AVL));
	if(temp==NULL){
		printf("Insufficient Memory");
		exit(1);
	}
	temp->value=x;
	temp->left=NULL;
	temp->right=NULL;
	temp->parent=NULL;

	return(insertNode(root,temp));
}

AVL *insertNode(AVL *root, AVL *temp){
//inserts node pointed by temp to the AVL tree
	if(root==NULL)
		root=temp;
	else {
		temp->parent=root;
		if(root->value > temp->value)
			root->left=insertNode(root->left,temp);
		else
			root->right=insertNode(root->right,temp);	
	}
	return root;
}

AVL *search(AVL *root, int x){
//returns a pointer to the node with value x
	if(root==NULL || root->value==x) return (root);
	else if(root->value> x) return(search(root->left,x));
	return(search(root->right,x));
}

AVL *findMin(AVL *root){
//returns a pointer to the node with the minimum value
	if (root==NULL || root->left==NULL) return(root);
	return(findMin(root->left));
}

void printAVL(AVL *root,int tabs){
//tabs should be equal to the current height of the tree
  int i;
  if(root!=NULL){
  	printAVL(root->right,tabs+1);
  	for(i=0;i<tabs;i++) printf("\t");
  	printf("%3i\n",root->value);
  	printAVL(root->left,tabs+1);  		
  }  
}

AVL *deleteNode(AVL *root, int x){
//deletes the node with value x
}
