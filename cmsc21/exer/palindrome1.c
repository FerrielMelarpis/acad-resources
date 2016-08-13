#include <string.h>
#include <stdio.h>

int isPalindrome(char *s) {
    static int i; // automatically initialized i to zero
    int len = strlen(s);
    for(;i<len;i++)
        if(s[i] != s[len-i-1])
            return 0;
    return 1;
}

int main ()
{
    char str[100];
    printf("Enter string>> ");
    scanf(" %[^\n]", str);
    if(isPalindrome(str)) printf("%s is a palindrome\n", str);
    else printf("%s is not a palindrome\n", str);
    return 0;
}
