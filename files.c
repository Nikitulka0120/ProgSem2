#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void replaces(char *line, const char *name) {
    char *start = line;
    int max = 0;
    char *posMax = NULL;
    while (*start) {
        while (*start == ' ') {
            start++;
        }

        if (*start == '\0') break;

        char *end = start;

        while (*end != ' ' && *end != '\0') {
            end++;
        }

        int Wlen = end - start;

        if (Wlen > max) {
            max = Wlen;
            posMax = start;
        }

        start = end;
    }

    if (posMax) {
        int name_len = strlen(name);
        strncpy(posMax, name, name_len);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: ./program <input_file> <output_file>\n");
        return 1;
    }

    FILE *inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        perror("Ошибка открытия файла для чтения");
        return 1;
    }

    FILE *outputFile = fopen(argv[2], "w");
    if (!outputFile) {
        perror("Ошибка открытия файла для записи");
        fclose(inputFile);
        return 1;
    }

    char line[500];

    while (fgets(line, sizeof(line), inputFile)) {
        replaces(line, " Никита ");
        fputs(line, outputFile);
    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
