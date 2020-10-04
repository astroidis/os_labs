#include <stdio.h>


int main(){
    const char *str =
        "LO.REM IPSUM DOLOR SIT AMET CONSECTETUR ADIPISICING ELIT";

    int word_count = 0;
    for (char *p = str; (*p != '.') && (*p != 0); p++){
        char *c = p;

        while ((*p != ' ') && (*p != '.') && (*p != 0)){;
            p++;
        }

        word_count++;

        while (c < p){
            if (*c < 'A' || *c > 'Z'){
                word_count--;
                break;
            }
            c++;
        }
    }

    printf("Word count: %d\n", word_count);

    return 0;
}
