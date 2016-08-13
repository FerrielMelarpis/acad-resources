/****
NAME:
STUDENT NO:
SECTION:
DATE(MM-DD-YYY):

PROGRAM DESCRIPTION:
****/


#include<stdio.h>
#include<malloc.h>



    struct node{
    	int info;
    struct node *right;
    struct node *left;
};

typedef struct node *BST;
typedef struct node node;


BST makeempty(BST t){
}

BST find(BST t, int x){

}

BST findmin(BST t){

}

BST findmax(BST t){
}

BST insertnode(BST t, int x){
}

BST deletenode(BST t, int x){
}

void printtree_asc(BST t){
}

void printtree_desc(BST t){
}

main(){
    BST tree, pos;
    int ans;
    int val;
    tree=NULL;


        while(1){
			printf(" Binary Search Tree (BST)");
			printf("\n\n [1].\tInsert\n");
			printf(" [2].\tDelete\n");
			printf(" [3].\tMake Empty\n");
			printf(" [4].\tFind Minimum\n");
			printf(" [5].\tFind Maximun\n");
			printf(" [6].\tSearch\n");
			printf(" [7].\tPrint Ascending\n");
			printf(" [8].\tPrint Descending\n");
			printf(" [9].\tExit\n\n");
			printf(" Enter Choice: ");
        	scanf("%d", &ans);
        
		switch(ans){
            case 1:{
                	printf("\n Enter Value: ");
                	scanf("%d",&val);
                	tree=insertnode(tree,val);
            }
            break;
			
            case 2:{
                    if(tree!=NULL) {
                    	printf("\n Enter Value to be Deleted: ");
                    	scanf("%d",&val);
                    	tree=deletenode(tree,val);
					}
					else printf("\n Cannot Delete!! Empty BST!!");

            }
            break;
			
            case 3:{
                	tree = makeempty(tree);
                	printf("\n BST is now Empty!!");

            }
            break;
			
            case 4:{
                	pos=findmin(tree);
                	if (pos!=NULL)
                		printf("\n Minimum Value: %d",pos->info);
                	else
                		printf("\n Empty BST!! No Minimum Value.");
            }
            break;
            
			case 5:{
                	pos=findmax(tree);
                	if (pos!=NULL)
                		printf("\n Maximum Value: %d",pos->info);
                	else
                		printf("\n Empty BST!! No Maximum Value.");
            }
            break;
			
            case 6:{
                    if (tree!=NULL) {
                    	printf("\n Enter Value to be Searched: ");
                    	scanf("%d",&val);
                    	pos=find(tree, val);
                    	if (pos!=NULL)
                    		printf("\n %d is found in the BST",pos->info);
                    else
                    		printf("\n %d not found in the BST",val);
                }
                    else {
                    	printf("\n The BST is Empty!!");
                }
            }

            break;
            case 7:{
                    if(tree!=NULL) {
                    	printf("\n BST IN ASCENDING ORDER\n\n");
                    	printtree_asc(tree);
                }
                else printf("\n Empty BST!!");;
            }
            break;
			
            case 8:{
					if(tree!=NULL) {
                    	printf("\n BST IN DESCENDING ORDER\n\n");
                    	printtree_desc(tree);
					}
                else printf("\n Empty BST!!");
            }
            break;
			
            case 9:{
					tree = makeempty(tree);
					exit(0);
			}
            default:{
                	printf("\n\n Choose from 1 to 9 only!!");
            }//def
            break;
        }//switch
	}//while

}//main
