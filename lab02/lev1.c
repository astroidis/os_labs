#include <stdio.h>

int main(){
    unsigned char n, b;

    printf("Enter a number: ");
    scanf("%hhu", &n);
    printf("Enter bit no: ");
    scanf("%hhu", &b);

    printf("Cleared bit no %hhu in number %hhu: %hhu\n",
           b, n, (n & (~(1 << b))));

    return 0;
}
