#include <stdio.h>


int main(){
    unsigned char num, bitno;

    printf("Enter a number: ");
    scanf("%hhu", &num);

    printf("Enter number of bit (0-7): ");
    scanf("%hhu", &bitno);

    printf("Bit %hhu in number %hhu is %sset\n",
           bitno, num, (num & (1 << bitno) ? "" : "not "));

    return 0;
}
