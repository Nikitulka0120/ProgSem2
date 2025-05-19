#include <stdio.h>
#include <stdlib.h>
#include "translatorFuncs.h"

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Использование: %s input.txt dict.txt output.txt\n", argv[0]);
        return 1;
    }

    Dictionary dict;
    dict_init(&dict);

    load_dictionary(&dict, argv[2]);
    translate_file(&dict, argv[1], argv[3]);

    dict_free(&dict);
    return 0;
}
