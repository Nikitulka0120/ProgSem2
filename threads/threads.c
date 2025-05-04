#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define THREADS 4
#define N 5

pthread_mutex_t mutex;
pthread_cond_t cond;
int current_turn = 0;

typedef struct
{
    int thread_num;
    const char *messages[N + 1];
} thread_data_t;


void exit_func(void *arg)
{
    printf("Поток %d завершает свою работу.\n", *(int *)arg);
}

void *child(void *arg)
{
    thread_data_t *data = (thread_data_t *)arg;
    int thread_num = data->thread_num;
    pthread_cleanup_push(exit_func, &thread_num);

    for (int i = 0; i <= N; i++)
    {
        pthread_mutex_lock(&mutex);
        while (current_turn != thread_num)
        {
            pthread_cond_wait(&cond, &mutex);
        }

        printf("Поток %d: %s\n", data->thread_num, data->messages[i]);
        if (current_turn == THREADS)
        {
            current_turn = 0;
        }
        else
        {
            current_turn++;
        }
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutex);
    }

    pthread_cleanup_pop(0);
    return NULL;
}

int main(void)
{
    pthread_t string_threads[THREADS];
    thread_data_t thread_data[THREADS];

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    const char *messages[THREADS][N + 1] = {
        {"строка 0 потока 1", "строка 1 потока 1", "строка 2 потока 1", "строка 3 потока 1", "строка 4 потока 1", "строка 5 потока 1"},
        {"строка 0 потока 2", "строка 1 потока 2", "строка 2 потока 2", "строка 3 потока 2", "строка 4 потока 2", "строка 5 потока 2"},
        {"строка 0 потока 3", "строка 1 потока 3", "строка 2 потока 3", "строка 3 потока 3", "строка 4 потока 3", "строка 5 потока 3"},
        {"строка 0 потока 4", "строка 1 потока 4", "строка 2 потока 4", "строка 3 потока 4", "строка 4 потока 4", "строка 5 потока 4"}};

    for (int i = 0; i < THREADS; i++)
    {
        thread_data[i].thread_num = i + 1;
        memcpy(thread_data[i].messages, messages[i], sizeof(messages[i]));
        pthread_create(&string_threads[i], NULL, child, &thread_data[i]);
    }

    for (int i = 0; i <= N; i++)
    {
        pthread_mutex_lock(&mutex);
        while (current_turn != 0)
        {
            pthread_cond_wait(&cond, &mutex);
        }

        printf("Основной поток: строка %d\n", i);
        current_turn = 1;
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutex);
    }

    for (int i = 0; i < THREADS; i++)
    {
        pthread_join(string_threads[i], NULL);
    }
}