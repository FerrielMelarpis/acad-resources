/*
  (c)Ferriel Lisandro B. Melarpis
 	UV-5L
 	2012-01065
 	CAS BSCS
 	University Of The Philippines Los Banos

	"If your government shuts down the internet, shut down your government."

*/

// libraries needed
#include <stdio.h>// for standard input output
#include <string.h>// string functions
#include <ctype.h> // for cases and types functions
// function protoypes
void revWord(char *);
void revString(char *, char *);
// function definitions
void revString(char *a, char *b){
	int i = 0;
	char *c, *d;	
	char e[100];
	strcpy(b, a); // copy the string a to string b
	d = a; // copy the address of the first element in string a
	while(*d){ // processing the input string
		while(*d != ' ' && *d != '\0'){// comparing to the delimiters
			e[i] = *d;
			i++;
			d++;
		}	
		e[i] = '\0';// set the last value of the word to null terminator
		i = 0; // resets the value for another loop
		
		revWord(e); // function call for revWord
		
		c = e; // copy the address of the first element in string e
		
		while(*c){// copying the elements of the reversed word to the ouput string
			*b = *c;
			c++;
			b++;
		}
		if(*b == ' '){// advance to the next word
			b++;
		}
		
		d = b; // then copy the adress of the pointer b to reverse the other words
		
	}
}

void revWord(char *f){ // function that reverse the word
	int i, length;
	char *g, temp;
	
	length = strlen(f);
	g = f + length-1;
	if(length == 1){
		*f = toupper(*f);// makes uppercase
	}else{
		for(i=0;i<length/2;i++){// swapping the elements of the word
			if(i == 0)
				*g = toupper(*g);// makes uppercase
				
			temp = *f;	
			*f = *g;
			*g = temp;
			g--;
			f++;
		}
	}

}
//main
int main(){
	char input[100];
	char output[100];
	int i;
	printf("Enter String:\n>> ");
	gets(input);

	for(i=0;i<strlen(input);i++){
		input[i] = tolower(input[i]); // makes all the letter lowercase
	}
	
	revString(input, output);// function call for revString
	
	printf("Answer:\n>> ");
	printf("%s\n", output);// prints the reverse string

	return 0;
}

// end of program :)
