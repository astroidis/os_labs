/* Написать программу, приписывающую в конец файла его содержимое */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 50

int main(int argc, char *argv[]){
    if (argc != 2){
        fprintf(stderr, "Missing argument: filename\n");
        return -1;
    }

    char *filename = argv[1];
    int fd = open(filename, O_RDWR, 0440);
    if (fd == -1){
        perror("open");
        return -1;
    }

    off_t eof_pos = lseek(fd, -1, SEEK_END);
    off_t start_pos = lseek(fd, 0, SEEK_SET);

    char buf[BUFSIZE];
    ssize_t nread = 0;

    while(start_pos < eof_pos){
        nread = read(fd, buf, BUFSIZE-1);
        buf[BUFSIZE-1] = 0;

        start_pos = lseek(fd, 0, SEEK_CUR);
        if (start_pos > eof_pos){
            nread -= start_pos - eof_pos;
        }

        lseek(fd, -1, SEEK_END);
        write(fd, buf, nread);

        lseek(fd, start_pos, SEEK_SET);
    }

    close(fd);
    return 0;
}
