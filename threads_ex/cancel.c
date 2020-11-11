#include <unistd.h>
#include "threads_ex.h"

void * threadFunc(void *arg){
    printf("New thread started\n");  /* may be cancellation point */
    for (int i = 0; ; i++){
        printf("Loop %d\n", i);  /* may be cancellation point */
        sleep(1);  /* cancellation point */
    }
    /* not reached */
    return NULL;
}


int main(){
    pthread_t thr;
    thr = pthread_create(&thr, NULL, threadFunc, NULL);

    sleep(3);  /* allow new thread to run */

    pthread_cancel(thr);

    void *status;
    pthread_join(thr, &status);

    if (status == PTHREAD_CANCELED){
        printf("Thread was cancelled\n");
    }
    else {
        printf("Thread was not cancelled\n");
    }

    return 0;
}
