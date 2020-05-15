#include "memory.h"

struct memory *memory_create(int words)
{
  struct memory *m = (struct memory *)malloc(sizeof(struct memory));
  if (!m)
    ERR("Can't allocate memory for struct memory");
  m->data = (int8_t *)calloc(words, sizeof(int32_t));
  if (!m->data)
    ERR("Can't allocate %d words (32 bit) for memory", words);
 m->addr = 0;
 m->in = 0;
 m->size = words;
}

void memory_free(struct memory *m)
{
  free(m->data);
  free(m);
}
