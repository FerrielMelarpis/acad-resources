/*
 *   (C)Ferriel Lisandro B. Melarpis 
 *	UPLB 2012-01065
 *	CMSC123 CD-2L
 *	Program implementing stack that converts a given infix expression
 *	into its postfix form and checks for invalid cases 
 */

// libraries
#include <stdio.h> // standard input and output functions
#include <stdlib.h> // memory allocation functions

// color definitions
#define RED "\e[31m"
#define GRN "\e[32m"
#define YEL "\e[33m"
#define BLU "\e[34m"
#define MAG "\e[35m"
#define ITA "\e[3m"
#define BLD "\e[1m"
#define CLR "\e[m"
// macro constant
#define ERROR -1

// structure for stack
typedef struct stack Node;
struct stack{
  char c;
  Node *next;
};

// function prototypes
void push(Node *, char);
char tos(Node *);
char pop(Node *);
Node *createStack();
int isOperator(char);
int precedence(char);
int isValid(char *);
void concatenate(char *, char);
void convert(Node *, char *);
void errorType(int, int);
// function definitions

// function for creating stack
Node *createStack(){
  Node *s = (Node*)malloc(sizeof(Node));
  s->next = NULL;
  return s;
}

// function that checks if a character is an operation
int isOperator(char c){
  if(c=='+'||c=='-'||c=='*'||c=='/'){ return 2;}
  else if(c=='('||c==')'){ return 3;}
  else{ return 1;}
}

// function that returns the precedence value of a character
int precedence(char c){
  if(c=='+'||c=='-'){ return 2;}
  else if(c=='*'||c=='/'){ return 3;}
  else if(c=='('||c==')'){ return 4;}
  else{ return 1;}
}

// function that prints the type of error in the expression
void errorType(int n, int i){
  if(n!=0){
    fprintf(stderr, RED BLD"SYNTAX ERROR\n"CLR);
    if(n==1) printf(ITA RED"Error 1: "CLR GRN"No operations inside some set of parentheses at indices: %d, %d.\n"CLR, i, i+1);
    if(n==2) puts(ITA RED"Error 2: "CLR GRN"Some parentheses have no partner."CLR);
    if(n==3) puts(ITA RED"Error 3: "CLR GRN"First and/or Last character is an operator."CLR);
    if(n==4) printf(ITA RED"Error 4: "CLR GRN"Two or more adjacent operations from index: %d.\n"CLR, i);
    //if(n==6) puts(ITA RED"Error 5: "CLR GRN"Two or more adjacent variables."CLR);
    if(n==5) printf(ITA RED"Error 5: "CLR GRN"No operation detected in neccessary part of the expression. Check index: %d.\n"CLR, i);
  }
}

// function that checks the validity of an expression
int isValid(char *str){
  int i=0, n=0, c1=0, c2=0, op=0;
  // so this is the revised part for error detection
  /*types of error:
   * a+()
   * ab
   * a+b)
   * (a+b
   * ((a+b)
   * (a+b))
   * a++
   * a(b+c)
   * )a+b(
   * a+-b
   */
  while(str[i]!='\0'){
    if(str[i]=='('&&str[i+1]==')'){
      n = 1;
      errorType(n, i);
    }
    if(str[i]>='a'&&str[i]<='z'){
      if(str[i+1]=='('||str[i-1]==')'){
	n = 5;
	errorType(n, i);
      }
    }
    if(isOperator(str[i])==2&&isOperator(str[i+1])==2){
      n=4;
      errorType(n, i);
    }
    i++;
  }
  i=0;
  while(str[i]!='\0'){
    if(isOperator(str[i])==2) op++;
    if(str[i]=='(') c1++;
    if(str[i]==')') c2++;
    i++;
  }
  if(op==0){n=5; errorType(n, i);}
  if(c1!=c2){ n=2; errorType(n, i);}
  int length=0;
  while(str[length]!='\0') length++;
  if(isOperator(str[0])==2||str[0]==')'||isOperator(str[length-1])==2||str[length-1]=='('){ n=3; errorType(n, i);}
  
  if(n==0) return 0;
  else return ERROR;
  // I comment out this part because I'm a little bit confused about the error detecting part
  /*while(str[i]!='\0'){
    if(str[i]=='('&&str[i+1]==')'){
      n = 1;
      goto error;
    }
    i++;
  }
  i=0;
  while(str[i]!='\0'){
    if(str[i]>='a'&&str[i]<='z'){
      if(str[i+1]>='a'&&str[i+1]<='z'){
	n = 5;
	goto error;
      }
    }
    i++;
  }
  i=0;
  while(str[i]!='\0'){
    if(str[i]=='(') c1++;
    if(str[i]==')') c2++;
    i++;
  }
  if(c1!=c2){ n=2; goto error;}
  int length=0;
  while(str[length]!='\0'){length++;}printf("%d\n",length);
  if(isOperator(str[0])==2||str[0]==')'||isOperator(str[length-1])==2||str[length-1]=='('){ n=3; goto error;}
  
  i=0;
  while(str[i]!='\0'){
    if(isOperator(str[i])==2&&isOperator(str[i+1])==2){
      n=4;
      goto error;
    }
    i++;
  }
  error:*/
  /*if(n!=0){
    fprintf(stderr, RED BLD"SYNTAX ERROR\n"CLR);
    if(n==1) puts(ITA RED"Error 1: "CLR GRN"No operations inside some set of parentheses."CLR);
    if(n==2) puts(ITA RED"Error 2: "CLR GRN"Some parentheses have no partner."CLR);
    if(n==3) puts(ITA RED"Error 3: "CLR GRN"First and/or Last character is an operation."CLR);
    if(n==4) puts(ITA RED"Error 4: "CLR GRN"Two or more adjacent operations."CLR);
    if(n==5) puts(ITA RED"Error 5: "CLR GRN"Two or more adjacent variables"CLR);
    return ERROR;
  }else{
    puts(MAG"Expression is valid."CLR);
    return 0;
  }*/
}

void concatenate(char *str, char c){
  int i;
  for(i=0;str[i]!='\0';i++);
  str[i] = c;
  str[i+1] = '\0';
}

void convert(Node *top, char *str){
  int i;
  char tmp, a[50];
  a[0]='\0';
  
  printf(BLU BLD ITA"Postfix : " CLR);
  for(i=0;str[i]!='\0';i++){
    if(precedence(str[i])==1){
      concatenate(a,str[i]);
    }else if( precedence(tos(top)) >= precedence(str[i])){
      while( (precedence(tos(top)) >= precedence(str[i])) && (tos(top) != '(') && tos(top)!='\0' ){
        if(precedence(tmp=pop(top))!=4){
	  concatenate(a,tmp);
	}
      }
      push(top,str[i]);
    }else if(str[i]==')'){
      while(tos(top)!='('){
	if(precedence(tmp=pop(top))!=4){
	  concatenate(a,tmp);
	}
      }
        if(tos(top)=='('){
	  pop(top);
	}
    }else{
        push(top,str[i]);
    }
  }
    while(tos(top)!='\0'){
      if(precedence(tmp=pop(top))!=4){
	concatenate(a,tmp);
      }
    }
    printf(BLD MAG"%s\n"CLR, a);
}

// function that returns the top of the stack 
// returns null character if stack is empty
char tos(Node *top){
  return top->next==NULL?'\0':top->next->c;
}
// function that pops(delete) the top of the stack
// and also returns the deleted node
char pop(Node *top){
  char c = tos(top);
  if(c!='\0'){
    Node *tmp = top->next;
    top->next = top->next->next;
    free(tmp);
  }
  return c;
}
// function that inserts a node on top of the stack
void push(Node *top, char c){
  Node *tmp = createStack();
  tmp->c = c;
  tmp->next = top->next;
  top->next = tmp;
}

// main function returning 0 if successful
int main(void){
  Node *top = createStack();  
  char str[50];
  
  printf(GRN"Enter String>> "CLR);
  scanf("%s", str);
  if(isValid(str)==0){ 
    convert(top, str);
  }free(top);
  return 0;
}
/*
 * TEST CASES
 * a+b*c+(d*e+f)*g
 * postfix: abc*+de*f+g*+
 * 
 * 3+4*5/6
 * postfix: 345*6/+
 * 
 * (300+23)*(43-21)/(84+7)
 * postfix: 300 23 + 43 21 - * 84 7 + /
 */