#include <stdio.h>
#include <unistd.h>


int main(int argc, char *argv[]){
    if (argc != 2){
        fprintf(stderr, "Directory not specified\n");
        return -1;
    }

    char buf[255];
    if (getcwd(buf, 255) == NULL){
        perror("getcwd");
        return -1;
    }

    printf("Current working directory: %s\n", buf);

    if (chdir(argv[1]) == -1){
        perror("chdir");
        return -1;
    }

    if (getcwd(buf, 255) == NULL){
        perror("getcwd");
        return -1;
    }

    printf("Current working directory: %s\n", buf);
    return 0;
}
