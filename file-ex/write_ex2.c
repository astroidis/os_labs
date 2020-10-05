#include <stdio.h>


int main(){
    FILE *fp = fopen("text1.txt", "w");
    if (!fp){
        fprintf(stderr, "Error while opening file\n");
        return -1;
    }

    char c;
    while ((c = fgetc(stdin)) != EOF){
        fputc(c, fp);
    }

    fclose(fp);
    return 0;
}
