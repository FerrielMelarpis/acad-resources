/**
  * Infix to Postfix Expression Converter with Error Checking
  * Copyright (C) 2013 Jan Keith C. Darunday
  *
  * This program is free software; you can redistribute it and/or
  * modify it under the terms of the GNU General Public License
  * as published by the Free Software Foundation; either version 2
  * of the License, or (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program; if not, write to the Free Software
  * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
  */

#include <stdio.h>
#include <stdlib.h>

//Definitions for easy printing of color hex codes.
#define NRM  "\x1B[m"
#define RED  "\x1B[31m"
#define GRN  "\x1B[32m"
#define ORN  "\x1B[33m"
#define BLU  "\x1B[34m"
#define MAG  "\x1B[35m"
#define CYN  "\x1B[36m"
#define WHT  "\x1B[37m"
#define BLD  "\x1B[1m"

typedef struct nodetag node;
struct nodetag{
    node *next;
    char c;
};

int parse2(char c);

//Validates our expression and checks for different kinds of errors.
int validate(const char *s){
    int error = 0,i;

    int level = 0;
    int opsperlevel[10],levelactive[10];

    for(i=0;i<10;i++){
        opsperlevel[i] = 0;
        levelactive[i] = 0;
    }

    for(i=0;s[i]!='\0';i++){
        if(s[i]=='(') level++;
        if(s[i]==')') level--;
        levelactive[level+5]=1;
        if(parse2(s[i])==2)
            opsperlevel[level+5]++;
    }

    for(i=0;i<10;i++){
        if(levelactive[i] == 1 && opsperlevel[i] == 0){error=1;break;}
    }

    if(level!=0){
        error=2;
    }

    for(i=0;s[i+1]!='\0';i++){
        if(i==0 && parse2(s[i])==2){error=3;break;}
        if(parse2(s[i])==2&&parse2(s[i+1])==2){error=4;break;}
    }

    if(error>0){
        printf(RED "Syntax Error: " ORN);
        switch(error){
        case 1:printf("There is a set of parentheses with no operations in between");break;
        case 2:printf("There is an unequal balance of parentheses");break;
        case 3:printf("First character is an operation");break;
        case 4:printf("There are two subsequent operations");break;
        }
        printf(NRM "\n");
        return 0;
    } else {
        printf(GRN "Expression Valid." NRM "\n");
        return 1;
    }
}

//Identifies whether a character is an operation, a parenthesis or a normal character
int parse2(char c){
    return (c=='+'||c=='-'||c=='*'||c=='/')?2:c=='('||c==')'?3:1;
}

//Identifies the type of character and its level of precedence
int parse(char c){
    return (c=='+'||c=='-')?2:(c=='*'||c=='/')?3:c=='('||c==')'?4:1;
}

//Reads the character at the top of the stack
char top(node *js){
    return js->next==NULL?0:js->next->c;
}

//Adds character to the top of the stack
void push(node *js, char c){
    node *tmp = malloc(sizeof(node));
    tmp->next=js->next;
    js->next=tmp;
    tmp->c = c;
}

//Reads last character of stack and deletes it
char pop(node *js){
    char ret = top(js);
    if(ret!=0){
        node *tmp = js->next;
        js->next=js->next->next;
        free(tmp);
    }
    return ret;
}

//Add character to the end of the string
void append(char *s, char c){
    int len;
    for(len=0;s[len]!='\0';len++);
    s[len]=c;
    s[len+1]=0;
}

//For debugging purposes only, prints the whole stack
void printstack(node *js){
    node *tmp=js->next;
    while(tmp!=NULL){
        putchar(tmp->c);
        tmp=tmp->next;
    }
    putchar('\n');
}

//Prints the postfix of string *s using the stack specified in *js
void postfix(node *js, const char *s){
    int i;
    char tmp;
    char fin[100];
    fin[0]=0;

    printf(GRN "Result is : " NRM);
    for(i=0;s[i]!='\0';i++){
        if(parse(s[i])==1){
            append(fin,s[i]);
        }else if( parse(top(js)) >= parse(s[i])){
            while( (parse(top(js)) >= parse(s[i])) && (top(js) != '(') && top(js)!=0 ){
                if(parse(tmp=pop(js))!=4)append(fin,tmp);
            }
            push(js,s[i]);
        }else if(s[i]==')'){
            while(top(js)!='(')if(parse(tmp=pop(js))!=4)append(fin,tmp);
            if(top(js)=='(')pop(js);
        }else{
            push(js,s[i]);
        }

        //Uncomment to debug how the stack moves
        /*printf("Stack is now : ");
        printstack(js);
        printf("Array is now : %s\n",fin);*/
    }

    while(top(js)!=0)if(parse(tmp=pop(js))!=4)append(fin,tmp);
    printf(BLD WHT "%s" NRM "\n",fin);
}

//Our main function
int main(){
    node *h = malloc(sizeof(node));
    h->next=NULL;

    printf(MAG "Enter expression: " ORN);

    char s[100];
    scanf("%[^\n]",s);
    printf(NRM);
    if(validate(s)==1)postfix(h,s);

    /*//postfix(h,"a+b*c-d/e*f");

      /*
        (300+23)*(43-21)/(84+7)
        (a+b*c-d)/(e*f)

    //postfix(h,"(a+b*c-d)/(e*f)");
    printf("%d\n", validate("(abc)"));
    printf("%d\n", validate("abc"));
    printf("%d\n", validate("+abc"));
    printf("%d\n", validate("a+*bc"));
    printf("%d\n", validate("a*bc"));
    //postfix(h, "");*/
    free(h);
}
