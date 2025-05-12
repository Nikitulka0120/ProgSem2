#ifndef SORTING_H
#define SORTING_H

void FillInc(int n, int A[n]);
void FillDec(int n, int A[n]);
void FillRand(int n, int A[n]);

int CheckSum(int n, int A[n]);
int RunNumber(int n, int A[n]);

int insertSort(int n, int A[n], int debug);
int shellSort(int n, int A[n], int debug);
int shellSortBetter(int n, int A[n], int debug);

void generateShellSequenceAsString(int n, char *buffer);
void generateCiuraSequenceAsString(int n, char *buffer);
void print(int n, int A[n]);

#endif
