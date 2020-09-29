#include <stdio.h>
#include <ctype.h>


int main(){
    char c;

    printf("Enter a character: ");
    scanf("%c", &c);

    if (isalpha(c))
        printf("This is a letter\n");
    else if (isdigit(c))
        printf("This is a number\n");
    else if (iscntrl(c))
        printf("This is a control character\n");
    else if (ispunct(c))
        printf("This is a punctuation character\n");
    else if (isspace(c))
        printf("This is a whitespace character\n");
    else
        printf("Unknown character :(\n");

    return 0;
}
