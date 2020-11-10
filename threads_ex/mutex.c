#include "threads_ex.h"

struct {
    int glob;
    pthread_mutex_t mtx;
} shared = {
    0,
    PTHREAD_MUTEX_INITIALIZER
};

void * increment(void * count){
    int c = *((int *) count);

    for (int i = 0; i < c; i++){
        pthread_mutex_lock(&shared.mtx);
        shared.glob++;
        pthread_mutex_unlock(&shared.mtx);
    }
    return NULL;
}


int main(int argc, char *argv[]){
    if (argc < 2){
        fprintf(stderr, "Set increment");
        return -1;
    }

    int inc = atoi(argv[1]);

    // create threads
    pthread_t thr1, thr2, thr3;
    int s = 0;
    s = pthread_create(&thr1, 0, increment, (void *) &inc);
    if (s != 0){
        fprintf(stderr, "pthread_create: %s\n", strerror(s));
        return -1;
    }

    s = pthread_create(&thr2, 0, increment, (void *) &inc);
    if (s != 0){
        fprintf(stderr, "pthread_create: %s\n", strerror(s));
        return -1;
    }

    s = pthread_create(&thr3, 0, increment, (void *) &inc);
    if (s != 0){
        fprintf(stderr, "pthread_create: %s\n", strerror(s));
        return -1;
    }

    // join threads
    s = pthread_join(thr1, 0);
    if (s != 0){
        fprintf(stderr, "pthread_join: %s\n", strerror(s));
        return -1;
    }

    s = pthread_join(thr2, 0);
    if (s != 0){
        fprintf(stderr, "pthread_join: %s\n", strerror(s));
        return -1;
    }

    s = pthread_join(thr3, 0);
    if (s != 0){
        fprintf(stderr, "pthread_join: %s\n", strerror(s));
        return -1;
    }

    printf("glob = %d\n", shared.glob);
    exit(EXIT_SUCCESS);
}
