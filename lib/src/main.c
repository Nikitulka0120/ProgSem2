#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcs.h"

int main()
{
    srand(time(NULL));
    printf("Процессор:\n");
    system("cat /proc/cpuinfo | grep 'model name' | head -1");

    struct Student students[N];

    printResult(selectionSort, N, students, "Выбором");
    printf("Размер данных массива: %ld байт\n", sizeof(students));
    printResult(countingSort, N, students, "Подсчетом");
    printf("Размер данных массива: %ld байт\n", sizeof(students));

    return 0;
}
