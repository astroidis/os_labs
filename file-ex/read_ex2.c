#include <stdio.h>


int main(){
    FILE *fp = fopen("text.txt", "r");
    if (!fp){
        fprintf(stderr, "Error while opening file\n");
        return -1;
    }

    char buf[255];
    while (fgets(buf, sizeof(buf), fp) != NULL){
        printf("%s", buf);
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
