#include <stdio.h>


int main(){
    FILE *fp = fopen("text.txt", "r");
    if (!fp){
        fprintf(stderr, "Error while opening file\n");
        return -1;
    }

    char c;
    while ((c = fgetc(fp)) != EOF){
        putchar(c);
    }

    if (feof(fp)){
        fprintf(stderr, "\nFile read successfully\n");
    }
    if (ferror(fp)){
        fprintf(stderr, "\nError while reading file\n");
    }

    fclose(fp);
    return 0;
}
