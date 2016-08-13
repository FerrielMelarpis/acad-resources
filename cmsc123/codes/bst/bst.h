/*
Exercise 4: Binary Search Tree
April 23, 2012
Fill up the following function definitions for BST. You are not allowed to change the parameters nor the return types of all the functions.
*/

#include<stdio.h>

typedef struct node_tag{
	int x;
	struct node_tag *parent;
	struct node_tag *left;
	struct node_tag *right;
}bst_node;

bst_node *search_node(bst_node **rootptr, int x){

}

bst_node *minimum(bst_node *node){

}

bst_node *successor(bst_node *node){

}

void delete_node(bst_node **rootptr, int x){

}

void insert_node(bst_node **rootptr, bst_node *temp){

}

void insert_value(bst_node **rootptr, int x){

}

void view(bst_node *root, int tabs){
	int i;
	if(root != NULL){
		view(root->right, tabs+1);
		for(i = 0; i < tabs; i++) printf("\t");
		
		printf("%2i\n", root->x);
		view(root->left, tabs+1);
	}
}