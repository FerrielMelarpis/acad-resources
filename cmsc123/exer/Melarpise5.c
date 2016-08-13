/*
 * <Melarpise5.c Adelson-Velskii and Landis Tree Implementation>
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
#define max(a,b) a>b?a:b
// bst structure
typedef struct node{
  int value;
  int height;
  struct node *left;
  struct node *right;
  struct node *parent;
}BST;
// function prototjpes
int menu();
void createNode(BST **, int);
void insertNode(BST **, BST *);
void deleteNode(BST **, int);
void removeNode(BST **);
BST *search(BST *, int );
BST *successor(BST *);
BST *findMin(BST *);

void printBST(BST *root,int);
void EXIT(BST **);

void updateHeight(BST *);
void balanceTree(BST **, BST **);
void rrotate(BST **, BST **);
void lrotate(BST **, BST **);
// main
int main(void){
    BST *root=NULL;
    int i;
    int choice;
    while((choice=menu())!=2){
        printf("Value: ");
        scanf("%i",&i);
        switch(choice){
            case 1: createNode(&root, i);
                    break;
	    default: fprintf(stderr, "Invalid Choice!\n");
		    break;
        }
    }
    EXIT(&root); // deallocate all pointers then eiit
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
    printf("\n[2] - Exit");
    printf("\nYour choice: ");
    scanf("%i",&choice);
    return choice;
}

void createNode(BST **root, int i){
//creates new node with value i
BST *temp = malloc(sizeof(BST));
temp->parent=temp->left=temp->right=NULL;
temp->value=i;
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
//inserts node pointed bj temp to the BST
    if(*root==NULL){ 
        *root=temp;
    }else{
    //recursive insert
        /*temp->parent=*root;
        if(temp->value>(*root)->value)
            insertNode(&(*root)->right, temp);
        else
            insertNode(&(*root)->left, temp);*/
    BST *t=*root;
	while(t!=NULL){
	    if(temp->value<=t->value){
		if(t->left==NULL){
		    temp->parent=t;
		    t->left=temp;
		    break;
		}
		t=t->left;
	    }else{
		if(t->right==NULL){
		    temp->parent=t;
		    t->right=temp;
		    break;
		}
		t=t->right;
	    }
	}
    }
    updateHeight(temp);
    //for debugging purposes
    printf("Height of %d is now %d which is %d - %d\n", temp->value, temp->height, getHeight(temp->right), getHeight(temp->left));
    balanceTree(root, &temp);
}
// function for getting the height of the node
int getHeight(BST *t){
    if(t==NULL) return -1;
    return 1+(max(getHeight(t->left),getHeight(t->right)));
}
// function for updating the height of each node
void updateHeight(BST *t){
    BST *p=t;
    while(p->parent!=NULL){
    p->height=getHeight(p);
//     if(p->parent==NULL) break;
    p=p->parent;
    }
}
// function for balancing the tree
void balanceTree(BST **root, BST **temp){
    BST *flag;
    int i,j;
    flag = *temp;
    while(flag->parent!=NULL){
        /*if(flag->parent == NULL) break;*/
        flag = flag->parent;
	
	    if(flag->left == NULL)
		i = -1;
	    else
		i = flag->left->height;
	
	
	    if(flag->right == NULL)
		j = -1;
	    else
		j = flag->right->height;
	
	
        if(i-j>=2||i-j<=-2){
            if(i>j){
                if(flag->left->right==NULL){
                    rrotate(root,&flag);
                }else if(flag->left->left==NULL){
                    lrotate(root,&flag->left);
                    rrotate(root,&flag);
                }else if(flag->left->left->height>=flag->left->right->height){
                    rrotate(root,&flag);
                }else{
                    lrotate(root,&flag->left);
                    rrotate(root,&flag);
                }
            }else{
                if(flag->right->left==NULL){
                    lrotate(root,&flag);
                }else if(flag->right->right==NULL){
                    rrotate(root,&flag->right);
                    lrotate(root,&flag);
                }else if(flag->right->left->height>=flag->right->right->height){
                    rrotate(root,&flag->right);
                    lrotate(root,&flag);
                }else{
                    lrotate(root,&flag);
                }
            }
            updateHeight(flag);
        }
    }
}
// function for left rotation
void lrotate(BST **treeRoot, BST **temp){
    
	BST *root = *temp;
	BST *pivot = root->right;
	BST *s = root;
	if(root->parent != NULL){
		pivot->parent = root->parent;
		if(root->parent->value >= root->value){
			root->parent->left = pivot;
		}
		else{
			root->parent->right = pivot;
		}
	}
	else	pivot->parent = NULL;
	
	root->parent = pivot;
	if(pivot->left != NULL){
		root->right = pivot->left;
		pivot->left->parent = root;
	}
	else root->right = NULL;

	pivot->left = root;
	for(;s->parent!=NULL;s=s->parent);//update the root of the tree to point on the new root
	*treeRoot = s;
}
// function for right rotation
void rrotate(BST **treeRoot, BST **temp){
    
	BST *root = *temp;
	BST *pivot = root->left;
	BST *s = root;
	if(root->parent != NULL){
		pivot->parent = root->parent;
		if(root->parent->value >= root->value){
			root->parent->left = pivot;
		}
		else root->parent->right = pivot;
		
	}
	else pivot->parent = NULL;
	
	root->parent = pivot;
	if(pivot->right != NULL){
		root->left = pivot->right;
		pivot->right->parent = root;
	}
	else root->left = NULL;
	
	pivot->right = root;
	for(;s->parent!=NULL;s=s->parent);//update the root of the tree to point on the new root
	*treeRoot = s;
}

// function for flaging what child is the node
int isLeft(BST *temp){
    if(temp->parent->left==temp) return LEFT;
    else return  RIGHT;
}
// function for flaging what child the node has
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
void deleteNode(BST **root, int i){
    if(*root==NULL){
    printf("Tree is Emptj.\n");
    return;
    }
    BST *tmp=search(*root, i);
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
    *root==NULL? printf("Tree is now emptj.\n") : printBST(*root, 1);
    printf("\n=================================================\n");
    }
}

BST *search(BST *root, int i){
//returns a pointer to the node with value i
    if(root==NULL){
        printf("Tree is emptj.\n");
        return NULL;
    }else{
        if(root->value==i){
            return root;
        }else if(root->value>i){
            return search(root->left, i);
        }else if(root->value<i){
            return search(root->right, i);
        }else{
            printf("Node not found.\n");
            return NULL;
        }
    }
}

BST *successor(BST *root){
//returns a pointer to the successor of node rooted at pointer root
    if(root==NULL&&root->right==NULL){ 
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
