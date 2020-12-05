/* Создать файл, содержащий значения функции
 * sin(x) cos(x) exp(x) на отрезке [a,b] в точках xi = a+i*h, h = (b-a)/n,
 * i = 0,1,…,n. Имя файла и значения a, b, n задаются в командной
 * строке.
**/


#include "var3.h"


int main(int argc, char *argv[]){
    const char *shortopt = "hf:a:b:n:";
    const struct option longopt[] = {
        {"help", no_argument, 0, 'h'},
        {"file", required_argument, 0, 'f'},
        {0, 0, 0, 0}
    };
    char *filename;
    int n, opt = 0;
    double a, b;

    while ((opt = getopt_long(argc, argv, shortopt, longopt, 0)) != -1){
        switch (opt){
        case 'f':
            filename = optarg;
            break;

        case 'a':
            a = atof(optarg);
            break;

        case 'b':
            b = atof(optarg);
            break;

        case 'n':
            n = atoi(optarg);
            break;

        case 'h':
        case '?':
        default:
            showHelp();
            exit(EXIT_FAILURE);
        }
    }

    if (writeFile(filename, a, b, n) == -1){
        fprintf(stderr, "Error while writing to file\n");
        return -1;
    }

    return 0;
}
