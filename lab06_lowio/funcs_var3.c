#include "var3.h"


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


int writeFile(char *filename, double start, double stop, int nsteps){
    int fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0640);
    if (fd == -1){
        return -1;
    }

    char *header = "x\t\tsin(x)\tcos(x)\texp(x)\n";
    if (write(fd, header, strlen(header)) < strlen(header)){
        close(fd);
        return -1;
    }

    double h = (stop - start) / nsteps;
    char buf[50];
    for (double x = start; x < stop + h/2; x += h){
        double x_sin = sin(x);
        double x_cos = cos(x);
        double x_exp = exp(x);

        sprintf(buf, "%.2lf\t%.2lf\t%.2lf\t%.2lf\n", x, x_sin, x_cos, x_exp);
        
        if (write(fd, buf, strlen(buf)) < strlen(buf)){
            close(fd);
            return -1;
        }
    }

    close(fd);
    return 0;
}