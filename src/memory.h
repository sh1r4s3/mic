#include <stdlib.h>
#include <string.h>
#include "misc.h"

struct memory
{
    char in; // rd, wr, fetch
    int addr;
    int size;
    int8_t *data;
};

enum memory_instruction {rd = 0, wr = 1, fetch = 2};

struct memory *memory_create(int words);
void memory_free(struct memory *m);
int memory_get_word();
int memory_set_word();
char memory_get_byte();
