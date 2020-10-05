#include <stdio.h>


typedef struct sigrecord {
    int code;
    char name[10];
    char descr[100];
} Sigrecord;


int main(){
    Sigrecord signals[4] = {
        {6, "SIGABRT", "Abort process"},
        {11, "SIGSEGV", "Invalid memory reference"},
        {19, "SIGSTOP", "Stop process for later resumption"},
        {0, 0, 0, 0}
    };

    FILE *fp = fopen("text2.txt", "wb");
    if (!fp){
        perror("Can not open file");
        return -1;
    }

    size_t size = sizeof(Sigrecord);

    if (fwrite(signals, size, 4, fp) != 4){
        perror("fwrite");
        return -1;
    }

    fclose(fp);
    return 0;
}
