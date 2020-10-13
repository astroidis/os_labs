#include <stdio.h>


int main(int argc, char *argv[]){
    if (argc != 3){
        fprintf(stderr, "Old and/or new path not specified\n");
        return -1;
    }

    if (rename(argv[1], argv[2]) == -1){
        perror("rename");
        return -1;
    }

    return 0;
}
