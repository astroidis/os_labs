#include <stdio.h>

int main(){
    unsigned short num = 20480;
    unsigned short reverse = 0;
    printf("%u\n", SIZE);
    
    for (int i = 0; i < SIZE; i++){
        if (num & (1 << i))
            reverse |= 1 << (SIZE - i - 1);
    }

    printf("%hu\n", reverse);

    return 0;
}
