#include "shift.h"

void shift_sll8(char *line, int size)
{
    if (!line)
        return;

    if (size > 8)
    {
        for (int i = size - 9; i >= 0; --i)
        {
            line[i + 8] = line[i];
            line[i] = 0;
        }
    }
    else
    {
        for (int i = 0; i < size; ++i)
        {
            line[i] = 0;
        }
    }
}

void shift_sra1(char *line, int size)
{
    if (!line)
        return;

    for (int i = 0; i < size - 1; ++i)
    {
        line[i] = line[i + 1];
    }
}
