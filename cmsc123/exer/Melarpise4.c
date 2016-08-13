/*
 * <Melarpise4.c Binary Search Tree Implementation>
 *  Copyright (C) <2014>  <Ferriel Lisandro B. Melarpis>
 *  NOTE:
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
// libraries
#include<stdio.h>
#include<stdlib.h>
// precompiler definitions
#define LEFT 10
#define RIGHT 20
// bst structure
typedef struct node{
  int value;
  struct node *left;
  struct node *right;
  struct node *parent;
}BST;
// function prototypes
int menu();
void createNode(BST **root, int x);
void insertNode(BST **root, BST *temp);
void deleteNode(BST **root, int x);
void removeNode(BST **);
BST *search(BST *root, int x);
BST *successor(BST *root);
BST *findMin(BST *root);

void printBST(BST *root,int tabs);
void EXIT(BST **);
// main
int main(void){
    BST *root=NULL;
    int x;
    int choice;
    while((choice=menu())!=3){
        printf("Value: ");
        scanf("%i",&x);
        switch(choice){
            case 1: createNode(&root, x);
                    break;
            case 2: deleteNode(&root, x);    
        }
    }
    EXIT(&root); // deallocate all pointers then exit
    if(root==NULL){ 
	printf("Exited Successfully.\n");
	exit(EXIT_SUCCESS);
    }else{
	exit(EXIT_FAILURE);
    }
}
// function for deleting the BST
void EXIT(BST **root){
    while(*root!=NULL){
	removeNode(root);
    }
}
// menu function
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

void createNode(BST **root, int x){
//creates new node with value x
BST *temp = malloc(sizeof(BST));
temp->parent=temp->left=temp->right=NULL;
temp->value=x;
//calls insertNode to add the new node to the BST
    if(*root==NULL) printf("Tree is Empty.\n");
    else{ 
        printf("Previous Tree:\n");
        printBST(*root, 1);
        printf("\n=================================================\n");
    }
insertNode(root, temp);
printf("Tree after insertion:\n");
printBST(*root, 1);
printf("\n=================================================\n");
}

void insertNode(BST **root, BST *temp){
//inserts node pointed by temp to the BST
    if(*root==NULL){ 
        *root=temp;
    }else{
        temp->parent=*root;
        if(temp->value>(*root)->value)
            insertNode(&(*root)->right, temp);
        else
            insertNode(&(*root)->left, temp);
    }
}
// function for checking what child is the node
int isLeft(BST *temp){
    if(temp->parent->left==temp) return LEFT;
    else return  RIGHT;
}
// function for checking what child the node has
int hasOne(BST *temp){
    if(temp->left!=NULL&&temp->right==NULL) return LEFT;
    else if(temp->left==NULL&&temp->right!=NULL) return RIGHT;
    else return 0;
}
// function for removing the node from the tree
void removeNode(BST **root){
    BST *tmp=*root;
    if(tmp->left!=NULL&&tmp->right!=NULL){
	BST *s=successor(tmp);
	tmp->value=s->value;
	removeNode(&s);
    }else{
	if(tmp->left==NULL&&tmp->right==NULL){
	    if(tmp->parent!=NULL){
            if(isLeft(tmp)==LEFT){
                tmp->parent->left=NULL;
            }else{
                tmp->parent->right=NULL;
            }
		free(tmp);
	    }else{
		*root=NULL;
		free(*root);
        free(tmp);
	    }
	}else{
	    if(hasOne(tmp)==LEFT){
		if(tmp->parent==NULL){
		    tmp->left->parent=NULL;
		    *root=tmp->left;
		}else if(isLeft(tmp)==LEFT){
		    tmp->parent->left=tmp->left;
		    tmp->left->parent=tmp->parent;
		}else{
		    tmp->parent->right=tmp->left;
		    tmp->left->parent=tmp->parent;
		}
		free(tmp);
	    }else{
		if(tmp->parent==NULL){
		    tmp->right->parent=NULL;
		    *root=tmp->right;
		}else if(isLeft(tmp)==LEFT){
		    tmp->parent->left=tmp->right;
		    tmp->right->parent=tmp->parent;
		}else{
		    tmp->parent->right=tmp->right;
		    tmp->right->parent=tmp->parent;
		}
		free(tmp);
	    }
	}
    }
}
// function for deleting nodes
void deleteNode(BST **root, int x){
    if(*root==NULL){
	printf("Tree is Empty.\n");
	return;
    }
    BST *tmp=search(*root, x);
    if(tmp==NULL){
	printf("Node not found.\n");
	return;
    }else{
	printf("Previous Tree:\n");
	printBST(*root, 1);
	printf("\n=================================================\n");
	if(tmp==*root){
	    removeNode(root);
	}else{
	    removeNode(&tmp);
	}
	printf("Tree after deletion:\n");
	*root==NULL? printf("Tree is now empty.\n") : printBST(*root, 1);
	printf("\n=================================================\n");
    }
}

BST *search(BST *root, int x){
//returns a pointer to the node with value x
    if(root==NULL){
        printf("Tree is empty.\n");
        return NULL;
    }else{
        if(root->value==x){
            return root;
        }else if(root->value>x){
            return search(root->left, x);
        }else if(root->value<x){
            return search(root->right, x);
        }else{
            printf("Node not found.\n");
            return NULL;
        }
    }
}

BST *successor(BST *root){
//returns a pointer to the successor of node rooted at pointer root
    if(root==NULL){ 
        printf("No successor.\n");
	return root;
    }else{
        return findMin(root->right);
    }
}

BST *findMin(BST *root){
//returns a pointer to the node with the minimum value
    if(root==NULL||root->left==NULL) 
	return root;
    else
	return findMin(root->left); 
}
// function for printing the BST
void printBST(BST *root,int tabs){
    int i;
    if(root!=NULL){
        printBST(root->right,tabs+1);
        for(i=0;i<tabs;i++) printf("\t");
        printf("%3i\n",root->value);
        printBST(root->left,tabs+1);          
    }
}