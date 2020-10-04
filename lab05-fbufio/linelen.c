/* the longest string */

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    if (argc < 2){
        fprintf(stderr, "Invalid number of arguments\n");
        return -1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp){
        fprintf(stderr, "Error while opening file\n");
        return -1;
    }

    int l, lenmax = 0;
    char buf[255];
    while (fgets(buf, 255, fp) != NULL){
        if ((l = (int) strlen(buf)) > lenmax){
            lenmax = l;
        }
    }

    printf("%d\n", lenmax);

    return 0;
}
