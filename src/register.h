#include <stdlib.h>
#include <string.h>
#include "misc.h"

struct reg
{
    char *data;
    const char *name;
    int bits;
};

struct reg *reg_create(int bits, const char *name);
void reg_free(struct reg *r);
