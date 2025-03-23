#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 10

struct route {
    char departures[50];
    char destination[50];
    int number;
};

const char* cities[] = {
    "Москва", "Санкт-Петербург", "Новосибирск", "Екатеринбург", "Казань",
    "Сочи", "Нижний Новгород", "Самара", "Омск", "Краснодар",
    "Уфа", "Красноярск", "Воронеж", "Пермь", "Волгоград"
};

void search(struct route array[N], int choice) {
    char searchDepartures[50];
    char searchDestination[50];
    int searchNumber;
    int found = 0;

    switch (choice) {
        case 1:
            printf("Введите пункт отправления для поиска: ");
            scanf("%s", searchDepartures);
            for (int i = 0; i < N; i++) {
                if (strcmp(array[i].departures, searchDepartures) == 0) {
                    printf("[%d] Город отправления \033[1;34m %s\033[1;0m Город прибытия: \033[1;32m %s\033[1;0m Номер маршрута: \033[1;36m %d\033[1;0m\n",
                           i, array[i].departures, array[i].destination, array[i].number);
                    found = 1;
                }
            }
            break;
        case 2:
            printf("Введите пункт назначения для поиска: ");
            scanf("%s", searchDestination);
            for (int i = 0; i < N; i++) {
                if (strcmp(array[i].destination, searchDestination) == 0) {
                    printf("[%d] Город отправления \033[1;34m %s\033[1;0m Город прибытия: \033[1;32m %s\033[1;0m Номер маршрута: \033[1;36m %d\033[1;0m\n",
                           i, array[i].departures, array[i].destination, array[i].number);
                    found = 1;
                }
            }
            break;
        case 3:
            printf("Введите номер маршрута для поиска: ");
            scanf("%d", &searchNumber);
            for (int i = 0; i < N; i++) {
                if (array[i].number == searchNumber) {
                    printf("[%d] Город отправления \033[1;34m %s\033[1;0m Город прибытия: \033[1;32m %s\033[1;0m Номер маршрута: \033[1;36m %d\033[1;0m\n",
                           i, array[i].departures, array[i].destination, array[i].number);
                    found = 1;
                }
            }
            break;
        default:
            printf("Неверный выбор.\n");
            return;
    }

    if (!found) {
        printf("Подходящий маршрут не найден\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Использование: ./испольняемый_файл.out бинарный_файл.dat\n");
        exit(1);
    }

    FILE *file = fopen(argv[1], "wb");
    if (file == NULL) {
        printf("In %s:%d Ошибка открытия файла:\n", __FILE__, __LINE__);
        exit(1);
    }

    srand(time(NULL));

    struct route array[N];
    printf("\n\n\nWriting to binary file..\n");
    for (int i = 0; i < N; i++) {
        array[i].number = rand() % 301;
        strncpy(array[i].departures, cities[rand() % 15], 50);
        strncpy(array[i].destination, cities[rand() % 15], 50);
        fwrite(&array[i], sizeof(struct route), 1, file);
        printf("[%d] Город отправления \033[1;34m %s\033[1;0m Город прибытия: \033[1;32m %s\033[1;0m Номер маршрута: \033[1;36m %d\033[1;0m\n",
               i, array[i].departures, array[i].destination, array[i].number);
    }

    fclose(file);

    memset(array, 0, sizeof(*array));
    file = fopen(argv[1], "rb");
    if (file == NULL) {
        printf("In %s:%d Error opening file\n", __FILE__, __LINE__);
        exit(1);
    }
    printf("\n\n\nReading from binary file..\n");
    fread(array, sizeof(struct route), N, file);
    for (int i = 0; i < N; i++) {
        printf("[%d] Город отправления \033[1;34m %s\033[1;0m Город прибытия: \033[1;32m %s\033[1;0m Номер маршрута: \033[1;36m %d\033[1;0m\n",
               i, array[i].departures, array[i].destination, array[i].number);
    }
    fclose(file);

    printf("По какому из полей вы бы хотели выполнить поиск?\n\033[1;34m1. Пункт отправления \033[1;0m\n\033[1;32m2. Пункт назначения\033[1;0m\n\033[1;36m3. Номер маршрута\033[1;0m\nВведите номер подходящего варианта: ");
    int choose;
    scanf("%d", &choose);

    search(array, choose);

    return 0;
}
