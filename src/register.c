#include "register.h"

struct reg *reg_create(int bits, const char *name)
{
    struct reg *r = (struct reg *)malloc(sizeof(struct reg));
    if (!r)
        ERR("Can't allocate memory for struct reg %s", name);
    r->data = (char *)calloc(bits, sizeof(char));
    if (!r->data)
        ERR("Can't allocate memory for reg %s", name);
    memset(r->data, 0, sizeof(char)*bits);

    r->name = name;
    r->bits = bits;

    return r;      
}

void reg_free(struct reg *r)
{
    free(r->data);
    free(r);
}
