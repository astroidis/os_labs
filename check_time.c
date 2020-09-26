#include <stdio.h>

int main(){
    char h = 25;
    char m = 10;
    char s = 10;

    if ((h < 0) || (h > 23)){
        return -1;
    }

    if ((m < 0) || (m > 59)){
        return -1;
    }

    if ((s < 0) || (s > 59)){
        return -1;
    }
        
    printf("Correct time\n");
    return 0;
}
