/* print lines of file where occurs given string */

#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[]){
    if (argc < 3 || !strcmp(argv[1], "--help")){
        fprintf(stderr, "Parameters: filename string\n"
                "\tfilename: file to search the string\n"
                "\tstring: text to search in file\n");
        return -1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp){
        fprintf(stderr, "Error while opening file\n");
        return -1;
    }

    char buf[255];
    while (fgets(buf, 255, fp) != NULL){
        if (strstr(buf, argv[2])){
            printf("%s\n", buf);
        }
    }

    return 0;
}
