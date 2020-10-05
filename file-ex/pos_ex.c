#include <stdio.h>


int main(){
    FILE *fp = fopen("text1.txt", "r");
    if (!fp){
        fprintf(stderr, "Error opening file\n");
        return -1;
    }

    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);
    printf("File size: %lu\n", size);

    fclose(fp);
    return 0;
}
