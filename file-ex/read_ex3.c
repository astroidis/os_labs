#include <stdio.h>


typedef struct sigrecord {
    int code;
    char name[10];
    char descr[100];
} Sigrecord;


int main(){
    Sigrecord signals[4];

    FILE *fp = fopen("text2.txt", "rb");
    if (!fp){
        perror("Can not open file");
        return -1;
    }

    size_t size = sizeof(Sigrecord);

    if (fread(signals, size, 6, fp) != 6){
        if (ferror(fp)){
            perror("fread");
            return -1;
        }
        if (feof(fp)){
            fprintf(stderr, "EOF reached\n");
        }
    }
    fclose(fp);

    for (Sigrecord *sigp = signals;
         sigp->code != 0 && sigp->name != 0 && sigp->descr != 0;
         sigp++)
    {
        printf("Signal: %d %s %s\n", sigp->code, sigp->name, sigp->descr);
    }

    return 0;
}
