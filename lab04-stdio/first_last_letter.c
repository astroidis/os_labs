/* print words which first and last letter are different */

#include <stdio.h>


int main(){
    char text[255];
    printf("Enter text: ");
    scanf("%[^.]", text);

    char *p = text;
    char *c;
    for (char *p = text; (*p != 0); p++){
        char *c = p;

        while ((*p != ' ') && (*p != '.') && (*p != 0)){
            p++;
        }

        if (*c != *(p-1)){
            *p = 0;
            printf("%s\n", c);
        }

    }

    return 0;
}
