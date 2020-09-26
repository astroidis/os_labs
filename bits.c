#include <stdio.h>
#include <getopt.h>
#include <unistd.h>
#include <stdlib.h>


unsigned char check_n_bit(unsigned char num, unsigned char bitno){
    unsigned char mask = 1 << bitno;
    return (num & mask);
}

unsigned char set_n_bit(unsigned char num, unsigned char bitno){
    unsigned char mask = (1 << bitno);
    return (num | mask);
}

unsigned char clear_n_bit(unsigned char num, unsigned char bitno){
    unsigned char mask = ~(1 << bitno);
    return (num & mask);
}

int main(int argc, char *argv[]){
    // unsigned char num = 201; /* 1100 1001 */
    int opt = 0;
    unsigned char (*func) (unsigned char, unsigned char) = 0;
    unsigned char num = 0, bit = 0;
    char name[10];

    while((opt = getopt(argc, argv, "csln:b:")) != -1){
        switch (opt){
        case 'c':
            func = &check_n_bit;
            sprintf(name, "check");
            break;

        case 's':
            func = &set_n_bit;
            sprintf(name, "set");
            break;

        case 'l':
            func = &clear_n_bit;
            sprintf(name, "clear");
            break;

        case 'n':
            num = (unsigned char) atoi(optarg);
            printf("num: %hhu\n", num);
            break;

        case 'b':
            bit = (unsigned char) atoi(optarg);
            printf("bit: %hhu\n", bit);
            break;

        default:
            printf("error\n");
        }
    }

    printf("%s bit no %hhu in num %hhu: %hhu\n",
           name, bit, num, func(num, bit));

    return 0;
}
