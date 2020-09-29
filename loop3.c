#include <stdio.h>


int main(){
    unsigned char num;
    int size = sizeof(unsigned char) * 8;

    printf("Enter a number: ");
    scanf("%hhu", &num);

    int i;
    for (i = 0; i < size; i++){
        if (num & (1 << i))
            break;
    }

    printf("First nonzero character from the right: %d\n", i);

    return 0;
}
