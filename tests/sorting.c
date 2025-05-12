#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sorting.h"

void FillInc(int n, int A[n]) {
    for (int i = 0; i < n; i++) A[i] = i;
}

void FillDec(int n, int A[n]) {
    for (int i = 0; i < n; i++) A[i] = n - i - 1;
}

void FillRand(int n, int A[n]) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) A[i] = rand() % n;
}

int CheckSum(int n, int A[n]) {
    int sum = 0;
    for (int i = 0; i < n; i++) sum += A[i];
    return sum;
}

int RunNumber(int n, int A[n]) {
    int runs = 1;
    for (int i = 0; i < n - 1; i++) {
        if (A[i] > A[i + 1]) runs++;
    }
    return runs;
}

void print(int n, int A[n]) {
    for (int i = 0; i < n; i++) printf("%d ", A[i]);
    printf("\n");
}

int insertSort(int n, int A[n], int debug) {
    int cmp = 0, moves = 0, temp;
    for (int i = 1; i < n; i++) {
        temp = A[i];
        int j = i - 1;
        while (j >= 0 && temp < A[j]) {
            cmp++;
            A[j + 1] = A[j];
            moves++;
            j--;
        }
        if (j >= 0) cmp++;
        A[j + 1] = temp;
        moves += 2;
    }
    if (debug) printf("Insert: M=%d C=%d\n", moves, cmp);
    return cmp + moves;
}

int shellSort(int n, int A[n], int debug) {
    int cmp = 0, moves = 0, h = 1;
    while (h < n / 3) h = 2 * h + 1;
    while (h >= 1) {
        for (int i = h; i < n; i++) {
            int temp = A[i], j = i - h;
            while (j >= 0 && temp < A[j]) {
                cmp++;
                A[j + h] = A[j];
                moves++;
                j -= h;
            }
            if (j >= 0) cmp++;
            A[j + h] = temp;
            moves++;
        }
        h /= 2;
    }
    if (debug) printf("Shell: M=%d C=%d\n", moves, cmp);
    return cmp + moves;
}

int shellSortBetter(int n, int A[n], int debug) {
    int ciura[] = {701, 301, 132, 57, 23, 10, 4, 1};
    int cmp = 0, moves = 0;
    for (int k = 0; k < sizeof(ciura)/sizeof(int); k++) {
        int h = ciura[k];
        if (h > n) continue;
        for (int i = h; i < n; i++) {
            int temp = A[i], j = i - h;
            while (j >= 0 && temp < A[j]) {
                cmp++;
                A[j + h] = A[j];
                moves++;
                j -= h;
            }
            if (j >= 0) cmp++;
            A[j + h] = temp;
            moves++;
        }
    }
    if (debug) printf("Shell(Ciura): M=%d C=%d\n", moves, cmp);
    return cmp + moves;
}

void generateShellSequenceAsString(int n, char *buffer) {
    int h = 1, count = 0, seq[20];
    while (h < n) {
        seq[count++] = h;
        h = 2 * h + 1;
    }
    int len = 0;
    for (int i = count - 1; i >= 0; i--) len += sprintf(buffer + len, "%d ", seq[i]);
    buffer[len] = '\0';
}

void generateCiuraSequenceAsString(int n, char *buffer) {
    int ciura[] = {701, 301, 132, 57, 23, 10, 4, 1}, len = 0;
    for (int i = 0; i < sizeof(ciura)/sizeof(int); i++) {
        if (ciura[i] <= n) len += sprintf(buffer + len, "%d ", ciura[i]);
    }
    if (len > 0 && buffer[len - 1] == ' ') buffer[len - 1] = '\0';
}
