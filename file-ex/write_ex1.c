#include <stdio.h>


int main(){
    char buf[255];
    while (fgets(buf, sizeof(buf), stdin) != NULL){
        fputs(buf, stdout);
    }

    return 0;
}
