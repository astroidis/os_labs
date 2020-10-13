#define _GNU_SOURCE

#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    if (argc != 3){
        fprintf(stderr, "Old and/or new path not specified\n");
        return -1;
    }

    if (symlink(argv[1], argv[2]) == -1){
        perror("symlink");
        return -1;
    }

    printf("Link created successfully\n");
    return 0;
}
