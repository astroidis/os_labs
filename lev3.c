#include <stdio.h>

int main(){
    unsigned char n = 204;
    int size = sizeof(unsigned char) * 8;    
    int counter = 0;

    for (int i = 0; i < size; i++){
        if (n & (1 << i))
            counter++;        
    }

    printf("%d\n", counter);

    return 0;
}
