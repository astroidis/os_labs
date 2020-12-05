#ifndef VAR3_H
#define VAR3_H

#include <math.h>
#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void showHelp();
int writeFile(char *filename, double start, double stop, int nsteps);

#endif // VAR3_H