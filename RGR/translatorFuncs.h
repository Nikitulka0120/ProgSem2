#ifndef TRANSLATORFUNCS_H
#define TRANSLATORFUNCS_H

typedef struct
{
    char *key;
    char *value;
} Entry;

typedef struct
{
    Entry *entries;
    int size;
    int capacity;
} Dictionary;

void dict_init(Dictionary *dict);
void dict_free(Dictionary *dict);
void dict_add(Dictionary *dict, const char *key, const char *value);
const char *dict_lookup(Dictionary *dict, const char *word_lower);
void load_dictionary(Dictionary *dict, const char *filename);

void translate_file(Dictionary *dict, const char *input_filename, const char *output_filename);

#endif
