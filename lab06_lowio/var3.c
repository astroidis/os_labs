/* Создать файл, содержащий значения функции
 * sin(x) cos(x) exp(x) на отрезке [a,b] в точках xi = a+i*h, h = (b-a)/n,
 * i = 0,1,…,n. Имя файла и значения a, b, n задаются в командной
 * строке.
**/

#include <math.h>
#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void showHelp();

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

    int fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0440);
    if (fd == -1){
        perror("open");
        exit(EXIT_FAILURE);
    }

    char *header = "x\t\tsin(x)\tcos(x)\texp(x)\n";
    write(fd, header, strlen(header));
    
    double h = (b - a) / n;
    char buf[50];
    for (double x = a; x < b + h/2; x += h){
        double x_sin = sin(x);
        double x_cos = cos(x);
        double x_exp = exp(x);

        sprintf(buf, "%.2lf\t%.2lf\t%.2lf\t%.2lf\n", x, x_sin, x_cos, x_exp);
        write(fd, buf, strlen(buf));
    }

    close(fd);
}

void showHelp(){
    fprintf(stderr, 
        "-h, --help\n"
        "\tDisplay help\n\n"
        "-f, --file\n"
        "\tSpecify output file name\n\n"
        "-a\n"
        "\tSet lower bound\n\n"
        "-b\n"
        "\tSet upper bound\n\n"
        "-n\n"
        "\tSet number of steps\n"
    );
}