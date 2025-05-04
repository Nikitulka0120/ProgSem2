#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

void FillMatrix(int n, int **Mat) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Mat[i][j] = 1;
        }
    }
}

void PrintMatrix(int n, int **Mat) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", Mat[i][j]);
        }
        printf("\n");
    }
}

typedef struct {
    int n;
    int start_row;
    int end_row;
    int **A;
    int **B;
    int **C;
} matrix_thread_data;

void *multiply_thread(void *arg) {
    matrix_thread_data *data = (matrix_thread_data *)arg;
    for (int i = data->start_row; i < data->end_row; i++) {
        for (int j = 0; j < data->n; j++) {
            data->C[i][j] = 0;
            for (int k = 0; k < data->n; k++) {
                data->C[i][j] += data->A[i][k] * data->B[k][j];
            }
        }
    }
    return NULL;
}

int main(void) {
    int n, matrix_threads;

    printf("Введите размер матрицы: ");
    scanf("%d", &n);
    printf("Введите количество потоков: ");
    scanf("%d", &matrix_threads);

    int **A = malloc(n * sizeof(int *));
    int **B = malloc(n * sizeof(int *));
    int **C = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        A[i] = malloc(n * sizeof(int));
        B[i] = malloc(n * sizeof(int));
        C[i] = malloc(n * sizeof(int));
    }

    FillMatrix(n, A);
    FillMatrix(n, B);

    pthread_t threads[matrix_threads];
    matrix_thread_data thread_data[matrix_threads];

    clock_t start_time = clock();

    int rows_per_thread = n / matrix_threads;
    int remaining_rows = n % matrix_threads;
    int current_row = 0;

    for (int i = 0; i < matrix_threads; i++) {
        thread_data[i].n = n;
        thread_data[i].A = A;
        thread_data[i].B = B;
        thread_data[i].C = C;

        int rows_for_this_thread = rows_per_thread + (i < remaining_rows ? 1 : 0);

        thread_data[i].start_row = current_row;
        thread_data[i].end_row = current_row + rows_for_this_thread;
        current_row += rows_for_this_thread;

        pthread_create(&threads[i], NULL, multiply_thread, &thread_data[i]);
    }

    for (int i = 0; i < matrix_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_t end_time = clock();

    double execution_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Время выполнения: %.4f секунд\n", execution_time);

    if (n <= 5) {
        printf("\nМатрица A:\n");
        PrintMatrix(n, A);

        printf("Матрица B:\n");
        PrintMatrix(n, B);

        printf("Результат умножения:\n");
        PrintMatrix(n, C);
    } else {
        printf("\nРазмер матрицы слишком большой для вывода.\n");
    }

    for (int i = 0; i < n; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}
