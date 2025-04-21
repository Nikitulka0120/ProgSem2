#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define THREADS 4
#define N 5
#define ARR 50

void FillRand(int n, int A[])
{
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        A[i] = rand() % 50;
    }
}

typedef struct {
    int thread_num;
    const char *messages[N+1];
} thread_data_t;

void exit_func(void *arg) {
    printf("Поток %d завершает свою работу.\n", *(int*)arg);
}

void* sleepSort(void* arg) {
    int value = *(int*)arg;
    sleep(value);
    printf("%d\n", value);
    return NULL;
}


void *child(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;
    int thread_num = data->thread_num;
    pthread_cleanup_push(exit_func, &thread_num);
    
    for (int i = 0; i <= N; i++) {
        printf("Поток %d: %s\n", data->thread_num, data->messages[i]);
        sleep(1);
    }

    pthread_cleanup_pop(0);
    return NULL;
}

int main(void) {
    pthread_t threads[ARR];
    thread_data_t thread_data[ARR];
    int A[ARR];
    FillRand(ARR, A);

    for (int i = 0; i <= ARR; i++) {
        pthread_create(&threads[i], NULL, sleepSort, &A[i]);
    }

    for (int i = 0; i < ARR; i++) {
        pthread_join(threads[i], NULL);
    }

    // const char *messages[THREADS][N+1] = {
    //     {"строка 0 потока 1", "строка 1 потока 1", "строка 2 потока 1", "строка 3 потока 1", "строка 4 потока 1", "строка 5 потока 1"},
    //     {"строка 0 потока 2", "строка 1 потока 2", "строка 2 потока 2", "строка 3 потока 2", "строка 4 потока 2", "строка 5 потока 2"},
    //     {"строка 0 потока 3", "строка 1 потока 3", "строка 2 потока 3", "строка 3 потока 3", "строка 4 потока 3", "строка 5 потока 3"},
    //     {"строка 0 потока 4", "строка 1 потока 4", "строка 2 потока 4", "строка 3 потока 4", "строка 4 потока 4", "строка 5 потока 4"}
    // };

    // for (int i = 0; i < THREADS; i++) {
    //     thread_data[i].thread_num = i + 1;
    //     memcpy(thread_data[i].messages, messages[i], sizeof(messages[i]));
    //     pthread_create(&threads[i], NULL, child, &thread_data[i]);
    // }

    // sleep(2);

    // for (int i = 0; i < THREADS; i++) {
    //     pthread_cancel(threads[i]);
    // }

    // for (int i = 0; i < THREADS; i++) {
    //     pthread_join(threads[i], NULL);
    // }

    // for (int i = 0; i <= N; i++) {
    //     printf("Основной поток: строка %d\n", i);
    // }

    return 0;
}