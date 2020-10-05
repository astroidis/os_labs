#ifndef SIGRECORD_H
#define SIGRECORD_H

typedef struct sigrecord {
    int code;
    char name[10];
    char descr[100];
} Sigrecord;

#endif
