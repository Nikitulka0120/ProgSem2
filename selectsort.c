#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define N 10

struct Student {
    char name[64];
    int math;
    int phy;
    int inf;
    int total;
};

const char* names[] = {
    "Вика", "Виктор", "Владислав", "Олег", "Миша", "Никита", "Настя", "Алина", "Евгения", "Евгений",
    "Петр", "Иван"
};


struct Student addStudent() {
    struct Student newStudent;
    strcpy(newStudent.name, names[rand()%(sizeof(names)/sizeof(names[0]))]);
    newStudent.math = rand()% 101;
    newStudent.phy = rand()% 101;
    newStudent.inf = rand()% 101;
    newStudent.total = newStudent.math + newStudent.phy + newStudent.inf;
    return newStudent;
}

void printStudentInfo(struct Student s) {
    printf("Имя: %s\n", s.name);
    printf("Математика: %d\n", s.math);
    printf("Физика: %d\n", s.phy);
    printf("Информатика: %d\n", s.inf);
    printf("Итог: %d\n\n", s.total);
}

void selectionSort(int n, struct Student A[]) {
    for (int i=0; i<n-1; i++) {
        int k=i;
        for (int j=i+1; j<n; j++) {
            if (A[j].total > A[k].total) {
                k=j;
            }
        }
        if (i != k) {
            struct Student temp = A[i];
            A[i]=A[k];
            A[k]=temp;
        }
    }
}

int main() {
    srand(time(NULL));
    struct Student students[N];
    for (int i = 0; i < N; i++) {
        students[i]=addStudent();
    }
    for (int i=0;i<N;i++) {
        printStudentInfo(students[i]);
    }
    selectionSort(N, students);
    printf("#########################\nСОРТИРОВАННЫЕ\n################################:\n");
    for (int i=0;i<N;i++) {
        printStudentInfo(students[i]);
    }

}
