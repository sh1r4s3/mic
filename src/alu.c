#include "alu.h"

struct ALU *alu_create(unsigned short units)
{
  struct ALU *alu = (struct ALU *)malloc(sizeof(struct ALU));
  if (!alu)
    ERR("Can't allocate memory for ALU");
  memset(alu, 0, sizeof(struct ALU));
  alu->n_units = units;

  alu->unit = (struct ALU_unit *)calloc(units, sizeof(struct ALU_unit));
  if (!alu->unit)
    ERR("Can't allocate memory for ALU units");
  memset(alu->unit, 0, sizeof(struct ALU_unit)*units);

  return alu;
}

void alu_free(struct ALU *alu)
{
  free(alu->unit);
  free(alu);
}

int alu_process(struct ALU *alu)
{
  // Basic sanity check
  if (!alu || !alu->unit)
    return -1;

  /*
    Let us try to simulate ALU as close to the circuit as possible.
    It is not an optimal way of course, but, it is WICKED FUN! Isn't it?
    operator(7) could make some help!
  */
  char inva = alu->inva & 0x1;
  char ena = alu->ena & 0x1;
  char enb = alu->enb & 0x1;
  char f0 = alu->f0 & 0x1;
  char f1 = alu->f1 & 0x1;
  char inc = alu->inc & 0x1;
  for (int i = 0; i < alu->n_units; ++i)
  {
    // Decoder
    char decoder = ( !f0 & !f1     |
                     !f0 & f1 << 1 |
                     f0 & !f1 << 2 |
                     f0 & f1 << 3 );
    // Logic
    char a = alu->unit[i].a & 0x1;
    char b = alu->unit[i].b & 0x1;
    char logic_in = a & ena ^ inva | b & enb << 1;
    char logic_out = ( logic_in & 0x1 & (logic_in & 0x2 >> 1) & decoder & 0x1        |
                       (logic_in & 0x1 | logic_in & 0x2 >> 1) & (decoder & 0x2 >> 1) |
                       !(logic_in & 0x2 >> 1) & (decoder & 0x4 >> 2) );

    // Full adder
    char carry_in = i != 0 ? alu->unit[i - 1].carry_out & 0x1 : inc;
    char carry_out = ( logic_in & 0x1 & (logic_in & 0x2 >> 1) & (decoder & 0x8 >> 3) |
                       carry_in & (logic_in & 0x1 ^ (logic_in & 0x2 >> 1)) & (decoder & 0x8 >> 3) );
    char sum = (logic_in & 0x1 ^ (logic_in & 0x2 >> 1) ^ carry_in) & (decoder & 0x8 >> 3);

    alu->unit[i].carry_out = carry_out;
    alu->unit[i].output = sum;
  }

  return 0;
}

char alu_overflow(struct ALU *alu)
{
  // Basic sanity check
  if (!alu || !alu->unit)
    return -1;

  return alu->unit[alu->n_units - 1].carry_out;
}

void alu_set_line(struct ALU *alu, char ab, char *line)
{
  for (int i = 0; i < alu->n_units; ++i)
  {
    switch (ab)
    {
    case 'a':
      alu->unit[i].a = line[i];
      break;
    case 'b':
      alu->unit[i].b = line[i];
      break;
    }
  }
}
