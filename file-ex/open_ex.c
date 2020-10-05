#include <stdio.h>


int main(){
    FILE *fp = fopen("text.txt", "r");
    if (!fp){
        perror("Can not open file");
        return -1;
    }
    else {
        printf("File opened successfully\n");
    }

    fclose(fp);
    return 0;
}
