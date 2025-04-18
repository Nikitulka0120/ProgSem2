#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcs.h"

const char *names[] = {
    "Вика", "Виктор", "Владислав", "Олег", "Миша", "Никита",
    "Настя", "Алина", "Евгения", "Евгений", "Петр", "Иван"};

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
    for (int i = 0; i < n; i++)
    {
        A[i] = addStudent();
    }

    clock_t start = clock();
    sortFunc(n, A);
    clock_t end = clock();

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Сортировка %s выполнена за: %f сек, для %d элементов\n\n", methodName, time_spent, N);
}
