/* how many times given character occurs in a given file */

#include <stdio.h>


int main(int argc, char *argv[]){
    if (argc < 3){
        fprintf(stderr, "Invalid argument number\n");
        return -1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp){
        fprintf(stderr, "Error while opening file\n");
        return -1;
    }

    char ch = *argv[2];
    char get;
    int count = 0;
    while((get = fgetc(fp)) != EOF){
        if (get == ch){
            count++;
        }
    }

    printf("%d\n", count);

    return 0;
}
