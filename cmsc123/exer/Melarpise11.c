/*    
 *   A C program implementation of Hash Table that add, delete and authenticate    
 *                a user's account from a file and/or from user input.
 *   NOTE: Vertices of the graph are labeled with integers.
 *   Copyright (C) 2014  Ferriel Lisandro B. Melarpis 
 *                 (University of the Philippines Los Banos)
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
// libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// predefined ASCII characters
#define RED "\e[31m"
#define GRN "\e[32m"
#define YEL "\e[33m"
#define BLU "\e[34m"
#define MAG "\e[35m"
#define CYN "\e[36m"
#define CLR "\e[m"
#define BRT "\e[1m"
#define BRED "\e[41m"
// structure for table rows
typedef struct node list;
struct node{
    char username[26];
    char password[21];
    list *next;
};
// structure for the hash table
typedef struct{
    list **table;
    int size;
}hash;
// function for constructing hash table
hash * createHashTable(int size){
    int i;
    hash *h=(hash*)malloc(sizeof(hash)*size);
    h->size=size;
    h->table=(list**)malloc(sizeof(list)*size);
    for(i=0;i<size;i++)
        h->table[i]=NULL;
    return h;
}
// function for printing menu
int menu(){
    int choice;
    show:
    printf("%s%s%s%s%s%s",
           CYN"__________MENU__________"CLR"\n",
           MAG"[1]"GRN" Add user\n",
           MAG"[2]"GRN" Delete user\n",
           MAG"[3]"GRN" Authenticate\n",
           MAG"[4]"GRN" Exit\n",
           YEL"Enter choice>> "CLR
    );
    scanf("%d", &choice);
    if(choice<1||choice>4){
        fprintf(stderr, BRED"ERROR:"CLR RED" Invalid Choice!\n"CLR);
        goto show;
    }
    return choice;
}
// hash function that returns a key for index usage
int getKey(char *str, int size){
    int c, sum=0;
    while(c=*str++)
        sum+=c;
    return sum%size;
}
// for debugging purposes
void printList(list *l){
    list *ptr=l;
    if(ptr==NULL){printf("List is empty.\n"); return;}
    while(ptr!=NULL){
        printf("username: %s -  password: %s\n", ptr->username, ptr->password);
        ptr=ptr->next;
    }printf("\n");
}
// function that adds user account to the hash table
int addUser(hash *h, char *username, char *password){
    int key=getKey(username, h->size);
    list *l=h->table[key];
    list *temp=(list*)malloc(sizeof(list));
    strcpy(temp->username, username);
    strcpy(temp->password, password);
    temp->next=NULL;
    if(h->table[key]==NULL){
        h->table[key]=temp;
        return 1;
    }
    for(;l!=NULL;l=l->next){
        if(strcmp(l->username, username)==0)
            return 0;
    }
    l=temp;
    return 1;
}
// function that deletes an account from the hash table
int deleteUser(hash *h, char *username, char *password){
    int key=getKey(username,h->size);
    list *l, *temp=h->table[key];
    if(temp==NULL){
        printf(RED"Account does not exist!\n"CLR);
        return 0;
    }
    if(strcmp(temp->username,username)==0){
        if(strcmp(temp->password,password)==0){
            h->table[key]=temp->next;
            free(temp);
            return 1;
        }else{
            printf(RED"Username and Password do not match.\n"CLR);
            return 0;
        }
    }
    for(l=temp->next;l!=NULL;l=l->next){
        if(strcmp(l->username,username)==0){
            if(strcmp(l->password,password)==0){
                list *tmp=l;
                l=l->next;
                free(tmp);
                return 1;
            }else{
                printf(RED"Username and Password do not match.\n"CLR);
                return 0;
            }
        }
    }
    return 0;
}
// function that checks if an account exists in the hash table 
int authenticate(hash *h, char *username, char *password){
    int key=getKey(username, h->size);
    list *l=h->table[key];
    if(l==NULL){
        printf(RED"Account does not exist!\n"CLR);
        return 0;
    }
    for(;l!=NULL;l=l->next){
        if(strcmp(l->username, username)==0){
            if(strcmp(l->password,password)==0){
                printf(CYN"Account authenticated.\n"CLR);
                return 1;
            }else{
                printf(RED"Username and Password do not match.\n"CLR);
                return 0;
            }
        }
    }
    return 0;
}
// function that gets the input accounts from a file if the file exists
int parse(hash *h){ 
    int i;
    char username[26], password[21];
    FILE *fp = fopen("accounts.txt", "r");
    if (fp==NULL){
        return 0;
    }
    for(i=0; i<h->size; i++) {
        fscanf(fp,"%s %s\n", username, password);
        if(addUser(h, username, password))
            printf(BLU BRT"Successfully Added.\n"CLR);
        else
            printf(BRED GRN"ERROR:"CLR RED" Account already exists!\n"CLR);
    }
    return 1;
    fclose(fp);
}
// function for getting the username and password input
void getParameter(char username[][26], char password[][21]){
    uname:
    printf(CYN"Enter username "GRN"[Min:6 Max:26]>> "CLR);
    scanf("%s", *username);
    if(strlen(*username)<6) goto uname;
    passwd:
    printf(CYN"Enter password "GRN"[Min:6 Max:21]>> "CLR);
    scanf("%s", *password);
    if(strlen(*password)<6) goto passwd;
}
// main
int main(int argc, char **argv){
    if(argc != 2){
        fprintf(stderr, BRED"USAGE"CLR CYN": %s <size>\n"CLR, argv[0]);
        exit(EXIT_FAILURE);
    }
    int size=atoi(argv[1]);
    hash *h=createHashTable(size);
    if(parse)
        printf(BLU BRT"File inputs successfully parsed.\n"CLR);
    else
        printf(BRED GRN"ERROR:"CLR RED" File not found!\n"CLR);
    
    int choice;
    char username[26], password[21];
    do{
        choice=menu();
        switch(choice){
            case 1:
                getParameter(&username, &password);
                if(addUser(h, username, password))
                    printf(BLU BRT"Successfully Added.\n"CLR);
                else
                    printf(BRED GRN"ERROR:"CLR RED" Account already exists!\n"CLR);
                break;
            case 2:
                getParameter(&username, &password);
                if(deleteUser(h, username, password))
                    printf(BLU BRT"Successfully Deleted.\n"CLR);
                else
                    printf(BRED GRN"ERROR:"CLR RED" Account not found!\n"CLR);
                break;
            case 3:
                getParameter(&username, &password);
                if(authenticate(h, username, password))
                    printf(BLU BRT"Logged In Successfully.\n"CLR);
                else
                    printf(BRED GRN"ERROR:"CLR RED" Account not found!\n"CLR);
                break;
        }
    }while(choice!=4);
    int i;
    for(i=0;i<h->size;i++)
        free(h->table[i]);
    free(h);
    printf(BRT GRN"Exited Successfully!\n"CLR);
    return EXIT_SUCCESS;
}
// END OF PROGRAM