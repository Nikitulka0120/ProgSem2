#define N 50000

struct Student
{
    char name[64];
    int math;
    int phy;
    int inf;
    int total;
};

struct Student addStudent();
void printStudentInfo(struct Student s);
void selectionSort(int n, struct Student A[]);
void countingSort(int n, struct Student A[]);
void printResult(void (*sortFunc)(int, struct Student[]), int n, struct Student A[], const char *methodName);

