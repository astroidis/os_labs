#include "threads_ex.h"

#define MAXLEN 256

struct {
    pthread_once_t var;
    pthread_key_t key;
} once = {
    PTHREAD_ONCE_INIT
};

void destructor(void *buf){
    free(buf);
}

void createKey(void){
    int s = pthread_key_create(&once.key, destructor);
    if (s != 0){
        fprintf(stderr, "pthread_key_create: %s\n", strerror(s));
        return;
    }
}


char * base(char *path){
    /*
    path         basename
    /usr/lib     lib
    /usr/        usr        (x)
    usr          usr
    /            /
    .            .
    ..           ..
    */

    /* allocate thread specific data */
    char *buf;
    int s;

    s = pthread_once(&once.var, createKey); /* first caller creates key */
    if (s != 0){
        fprintf(stderr, "pthread_key_create: %s\n", strerror(s));
        return NULL;
    }

    /* get address of allocated buffer */
    buf = pthread_getspecific(once.key);
    if (buf == NULL){  /* buffer not allocated */
        /* allocate buffer ad save its address */
        buf = malloc(MAXLEN);
        if (buf == NULL){
            fprintf(stderr, "Error: malloc()\n");
            return NULL;
        }

        s = pthread_setspecific(once.key, buf);
        if (s != 0){
            fprintf(stderr, "pthread_setspecific: %s\n", strerror(s));
            return NULL;
        }
    }


    char *last = 0;
    for (char *c = path; *c != 0; c++){
        if (*c == '/'){
            last = c;
        }
    }

    if (!strcmp(path, "/") || !strcmp(path, ".")
        || !strcmp(path, "..") || !last)
    {
        strncpy(buf, path, 255);
        buf[255] = 0;
        return buf;
    }

    if (last){
        strncpy(buf, last+1, 255);
        buf[255] = 0;
        return buf;
    }
}


void * threadFunc(void *arg){
    printf("Base thread_ex/base.c: %s\n", base("thread_ex/base.c"));
    return NULL;
}

int main(int argc, char *argv[]){
    pthread_t thr;

    pthread_create(&thr, NULL, threadFunc, NULL);
    pthread_join(thr, NULL);

    printf("Base usr/lib: %s\n", base("usr/lib"));
    return 0;
}
