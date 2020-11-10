#define _XOPEN_SOURCE

#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>

#define SOCK_PATH "/tmp/socket_ex"
#define BUF_SIZE 100
#define BACKLOG 5

void errorExit(char *msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

void fatal(char *msg){
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}
