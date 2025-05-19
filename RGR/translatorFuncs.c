#include "translatorFuncs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const char *cyr_upper[] = {
    "А", "Б", "В", "Г", "Д", "Е", "Ж", "З",
    "И", "Й", "К", "Л", "М", "Н", "О", "П",
    "Р", "С", "Т", "У", "Ф", "Х", "Ц", "Ч",
    "Ш", "Щ", "Ъ", "Ы", "Ь", "Э", "Ю", "Я", "Ё"};

const char *cyr_lower[] = {
    "а", "б", "в", "г", "д", "е", "ж", "з",
    "и", "й", "к", "л", "м", "н", "о", "п",
    "р", "с", "т", "у", "ф", "х", "ц", "ч",
    "ш", "щ", "ъ", "ы", "ь", "э", "ю", "я", "ё"};

#define CYR_COUNT (sizeof(cyr_upper) / sizeof(cyr_upper[0]))

void utf8_to_lower_custom(const char *src, char *dst)
{
    int i = 0, j = 0;
    while (src[i])
    {
        unsigned char c = (unsigned char)src[i];
        if ((c == 0xD0 || c == 0xD1) && src[i + 1])
        {
            char tmp[3] = {src[i], src[i + 1], 0};
            int found = 0;
            for (int k = 0; k < CYR_COUNT; k++)
            {
                if (strcmp(tmp, cyr_upper[k]) == 0)
                {
                    const char *lower = cyr_lower[k];
                    dst[j++] = lower[0];
                    dst[j++] = lower[1];
                    found = 1;
                    break;
                }
            }
            if (!found)
            {
                dst[j++] = src[i];
                dst[j++] = src[i + 1];
            }
            i += 2;
        }
        else
        {
            if (c < 128)
                dst[j++] = (char)tolower(c);
            else
                dst[j++] = src[i];
            i++;
        }
    }
    dst[j] = 0;
}

int is_word_char(unsigned char c)
{
    if (c == 0xD0 || c == 0xD1)
        return 1;
    return 0;
}

int is_first_letter_uppercase(const char *word)
{
    if (!word[0])
        return 0;

    if ((unsigned char)word[0] == 0xD0 || (unsigned char)word[0] == 0xD1)
    {
        if (!word[1])
            return 0;
        char first_letter[3] = {word[0], word[1], 0};
        for (int i = 0; i < CYR_COUNT; i++)
        {
            if (strcmp(first_letter, cyr_upper[i]) == 0)
                return 1;
        }
    }
    return 0;
}

void apply_case(const char *original, char *dst, const char *translation)
{
    int uppercase = is_first_letter_uppercase(original);
    int i = 0;
    if (uppercase && translation[0])
    {
        dst[0] = (char)toupper((unsigned char)translation[0]);
        i = 1;
    }
    else if (translation[0])
    {
        dst[0] = (char)tolower((unsigned char)translation[0]);
        i = 1;
    }

    for (; translation[i]; i++)
    {
        dst[i] = (char)tolower((unsigned char)translation[i]);
    }
    dst[i] = '\0';
}

void dict_init(Dictionary *dict)
{
    dict->size = 0;
    dict->capacity = 16;
    dict->entries = malloc(sizeof(Entry) * dict->capacity);
}

void dict_free(Dictionary *dict)
{
    for (int i = 0; i < dict->size; i++)
    {
        free(dict->entries[i].key);
        free(dict->entries[i].value);
    }
    free(dict->entries);
}

void dict_add(Dictionary *dict, const char *key, const char *value)
{
    if (dict->size >= dict->capacity)
    {
        dict->capacity *= 2;
        dict->entries = realloc(dict->entries, sizeof(Entry) * dict->capacity);
    }
    dict->entries[dict->size].key = strdup(key);
    dict->entries[dict->size].value = strdup(value);
    dict->size++;
}

const char *dict_lookup(Dictionary *dict, const char *word_lower)
{
    for (int i = 0; i < dict->size; i++)
    {
        if (strcmp(dict->entries[i].key, word_lower) == 0)
            return dict->entries[i].value;
    }
    return NULL;
}

void load_dictionary(Dictionary *dict, const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (!f)
    {
        perror("Ошибка открытия словаря");
        exit(1);
    }
    char key[256], val[256];
    while (fscanf(f, "%255s %255s", key, val) == 2)
    {
        char key_lower[256];
        utf8_to_lower_custom(key, key_lower);
        dict_add(dict, key_lower, val);
    }
    fclose(f);
}

void translate_file(Dictionary *dict, const char *input_filename, const char *output_filename)
{
    FILE *fin = fopen(input_filename, "r");
    FILE *fout = fopen(output_filename, "w");
    if (!fin || !fout)
    {
        perror("Ошибка открытия файлов");
        exit(1);
    }

    int c;
    char word[256];
    int pos = 0;

    while ((c = fgetc(fin)) != EOF)
    {
        unsigned char uc = (unsigned char)c;

        if (is_word_char(uc))
        {
            word[pos++] = c;

            if (uc >= 0xC0)
            {
                if ((uc & 0xE0) == 0xC0)
                {
                    c = fgetc(fin);
                    if (c != EOF)
                        word[pos++] = (char)c;
                }
                else if ((uc & 0xF0) == 0xE0)
                {
                    for (int i = 0; i < 2; i++)
                    {
                        c = fgetc(fin);
                        if (c != EOF)
                            word[pos++] = (char)c;
                    }
                }
            }

            continue;
        }
        else
        {
            if (pos > 0)
            {
                word[pos] = 0;

                char word_lower[256];
                utf8_to_lower_custom(word, word_lower);

                const char *trans = dict_lookup(dict, word_lower);
                if (trans)
                {
                    char applied[256];
                    apply_case(word, applied, trans);
                    fputs(applied, fout);
                }
                else
                {
                    fputs(word, fout);
                }
                pos = 0;
            }
            fputc(c, fout);
        }
    }

    if (pos > 0)
    {
        word[pos] = 0;

        char word_lower[256];
        utf8_to_lower_custom(word, word_lower);

        const char *trans = dict_lookup(dict, word_lower);
        if (trans)
        {
            char applied[256];
            apply_case(word, applied, trans);
            fputs(applied, fout);
        }
        else
        {
            fputs(word, fout);
        }
    }

    fclose(fin);
    fclose(fout);
}
