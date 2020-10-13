#include <stdio.h>
#include <dirent.h>


int main(int argc, char *argv[]){
    if (argc != 2){
        fprintf(stderr, "Directory not specified\n");
        return -1;
    }

    DIR *ds;
    if ((ds = opendir(argv[1])) == NULL){
        perror("opendir");
        return -1;
    }

    struct dirent *dp;
    while ((dp = readdir(ds)) != NULL){
        printf("%s\n", dp->d_name);
    }

    closedir(ds);
    return 0;
}
