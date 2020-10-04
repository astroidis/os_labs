#include <stdio.h>
#include <ctype.h>


typedef struct char_count{
    char ch;
    int count;
} CharCount;


CharCount * find_char(CharCount *counts, char c){
    for (CharCount *cc = counts; cc->ch != 0; cc++){
        if (cc->ch == c)
            return cc;
    }
    return NULL;
}


int main(int argc, char *argv[]){
    if (argc < 2){
        fprintf(stderr, "Invalid argument number\n");
        return -1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp){
        fprintf(stderr, "Error while opening file\n");
        return -1;
    }

    CharCount counts[27] = {
        {'a', 0},
        {'b', 0},
        {'c', 0},
        {'d', 0},
        {'e', 0},
        {'f', 0},
        {'g', 0},
        {'h', 0},
        {'i', 0},
        {'j', 0},
        {'k', 0},
        {'l', 0},
        {'m', 0},
        {'n', 0},
        {'o', 0},
        {'p', 0},
        {'q', 0},
        {'r', 0},
        {'s', 0},
        {'t', 0},
        {'u', 0},
        {'v', 0},
        {'w', 0},
        {'x', 0},
        {'y', 0},
        {'z', 0},
        {0, 0}
    };
    CharCount *cp;
    char c;
    while((c = fgetc(fp)) != EOF){
        c = tolower(c);
        if (cp = find_char(counts, c)){
            cp->count++;
        }
    }

    cp = counts;
    for (CharCount *cc = counts; cc->ch != 0; cc++){
        printf("%c %d\n", cc->ch, cc->count);
        if (cc->count > cp->count){
            cp = cc;
        }
    }

    printf("Most frequent character: %c, with count %d\n", cp->ch, cp->count);

    return 0;
}
