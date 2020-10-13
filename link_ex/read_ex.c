#define _GNU_SOURCE

#include <unistd.h>
#include <stdio.h>


int main(int argc, char *argv[]){
    if (argc != 2){
        fprintf(stderr, "Path not specified\n");
        return -1;
    }

    char buf[127];
    if (readlink(argv[1], buf, 126) == -1){
        perror("readlink");
        return -1;
    }

    buf[126] = 0;
    printf("Link %s points to %s\n", argv[1], buf);

    return 0;
}
