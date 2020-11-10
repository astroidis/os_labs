#include "threads_ex.h"

#define	MAXNITEMS 1000000
#define	MAXNTHREADS 100

/* глобальные переменные для всех потоков */
int	nitems;	 /* только для чтения потребителем и производителем */

int	buff[MAXNITEMS];
struct {
  pthread_mutex_t	mutex;
  int				nput;	/* следующий сохраняемый элемент */
  int				nval;	/* следующее сохраняемое значение */
} put = {
	PTHREAD_MUTEX_INITIALIZER
};

struct {
  pthread_mutex_t	mutex;
  pthread_cond_t	cond;
  int				nready;	/* количество готовых для потребителя */
} nready = {
PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER
};

void * produce(void *arg){
	for ( ; ; ) {
		pthread_mutex_lock(&put.mutex);
		if (put.nput >= nitems) {
			pthread_mutex_unlock(&put.mutex);
			return(NULL); /* массив заполнен, готово */
		}
		buff[put.nput] = put.nval;
		put.nput++;
		put.nval++;
		pthread_mutex_unlock(&put.mutex);

		pthread_mutex_lock(&nready.mutex);
		if (nready.nready == 0)
			pthread_cond_signal(&nready.cond);
		nready.nready++;
		pthread_mutex_unlock(&nready.mutex);

		*((int *) arg) += 1;
	}
}

void * consume(void *arg) {
	for (int i = 0; i < nitems; i++) {
		pthread_mutex_lock(&nready.mutex);
		while (nready.nready == 0)
			pthread_cond_wait(&nready.cond, &nready.mutex);
		nready.nready--;
		pthread_mutex_unlock(&nready.mutex);

		if (buff[i] != i)
			printf("buff[%d] = %d\n", i, buff[i]);
	}
	return(NULL);
}

int min(int a, int b){
    return (a < b ? a : b);
}

int main(int argc, char *argv[]){
	int i, nthreads, count[MAXNTHREADS];
	pthread_t tid_produce[MAXNTHREADS], tid_consume;

	if (argc != 3){
        fprintf(stderr, "Specify #items and #threads\n");
        return -1;
    }

	nitems = min(atoi(argv[1]), MAXNITEMS);
	nthreads = min(atoi(argv[2]), MAXNTHREADS);

	/* создание всех производителей и одного потребителя */
	for (i = 0; i < nthreads; i++) {
		count[i] = 0;
		pthread_create(&tid_produce[i], NULL, produce, &count[i]);
	}
	pthread_create(&tid_consume, NULL, consume, NULL);

	/* ожидание завершения производителей и потребителя */
	for (i = 0; i < nthreads; i++) {
		pthread_join(tid_produce[i], NULL);
		printf("count[%d] = %d\n", i, count[i]);
	}
	pthread_join(tid_consume, NULL);

	exit(0);
}
