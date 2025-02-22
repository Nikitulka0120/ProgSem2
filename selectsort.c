#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define N 50000

struct Student
{
    char name[64];
    int math;
    int phy;
    int inf;
    int total;
};

const char *names[] = {
    "Вика", "Виктор", "Владислав", "Олег", "Миша", "Никита", "Настя", "Алина", "Евгения", "Евгений",
    "Петр", "Иван"};

struct Student addStudent()
{
    struct Student newStudent;
    strcpy(newStudent.name, names[rand() % (sizeof(names) / sizeof(names[0]))]);
    newStudent.math = rand() % 101;
    newStudent.phy = rand() % 101;
    newStudent.inf = rand() % 101;
    newStudent.total = newStudent.math + newStudent.phy + newStudent.inf;
    return newStudent;
}

void printStudentInfo(struct Student s)
{
    printf("Имя: %s\n", s.name);
    printf("Математика: %d\n", s.math);
    printf("Физика: %d\n", s.phy);
    printf("Информатика: %d\n", s.inf);
    printf("Итог: %d\n\n", s.total);
}

void selectionSort(int n, struct Student A[])
{
    for (int i = 0; i < n - 1; i++)
    {
        int k = i;
        for (int j = i + 1; j < n; j++)
        {
            if (A[j].total > A[k].total)
            {
                k = j;
            }
        }
        if (i != k)
        {
            struct Student temp = A[i];
            A[i] = A[k];
            A[k] = temp;
        }
    }
}

void countingSort(int n, struct Student A[])
{
    int count[301] = {0};
    struct Student output[n];

    for (int i = 0; i < n; i++)
    {
        count[A[i].total]++;
    }
    for (int i = 299; i > 0; i--)
    {
        count[i - 1] += count[i];
    }
    for (int i = n - 1; i >= 0; i--)
    {
        output[count[A[i].total] - 1] = A[i];
        count[A[i].total]--;
    }

    for (int i = 0; i < n; i++)
    {
        A[i] = output[i];
    }
}

void printResult(void (*sortFunc)(int, struct Student[]), int n, struct Student A[], const char *methodName)
{
    // printf("------------------------ До сортировки ------------------------\n");
    for (int i = 0; i < n; i++)
    {
        A[i] = addStudent();
        // printStudentInfo(A[i]);
    }

    clock_t start = clock();
    sortFunc(n, A);
    clock_t end = clock();

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    // printf("------------------------ После сортировки (%s) ------------------------\n", methodName);
    // for (int i = 0; i < n; i++)
    // {
    //     printStudentInfo(A[i]);
    // }

    printf("Сортиовка %s выполнена за: %f сек, для %d элементов\n\n", methodName, time_spent, N);

}

void quickSort(struct Student A[], int left, int right) {
    if (left >= right) return;

    int pivot = A[(left + right) / 2].total;
    int i = left, j = right;

    while (i <= j) {
        while (A[i].total > pivot) i++;
        while (A[j].total < pivot) j--;

        if (i <= j) {
            struct Student temp = A[i];
            A[i] = A[j];
            A[j] = temp;
            i++;
            j--;
        }
    }

    if (left < j) quickSort(A, left, j);
    if (i < right) quickSort(A, i, right);
}

int main()
{
    srand(time(NULL));
    printf("Процессор:\n");
    system("cat /proc/cpuinfo | grep 'model name' | head -1");

    struct Student students[N];

    printResult(selectionSort, N, students, "Выборотм");
    printf("Размер данных массива: %ld байт\n", sizeof(students));
    printResult(countingSort, N, students, "Подсчетом");
    printf("Размер данных массива: %ld байт\n", sizeof(students));
    //  printf("------------------------ До сортировки ------------------------\n");
    for (int i = 0; i < N; i++)
    {
        students[i] = addStudent();
        // printStudentInfo(students[i]);
    }

    clock_t start = clock();
    quickSort(students, 0, N-1);
    clock_t end = clock();

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    // printf("------------------------ После сортировки (быстрая) ------------------------\n");
    // for (int i = 0; i <N; i++)
    // {
    //     printStudentInfo(students[i]);
    // }

    printf("Сортиовка быстрая выполнена за: %f сек, для %d элементов\n\n",time_spent, N);

    return 0;
}
