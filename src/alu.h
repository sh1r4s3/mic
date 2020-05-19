#include <stdlib.h>
#include <string.h>
#include "misc.h"

/*
 * This structures describes a state of a simple ALU module.
 * docs/ALU.md describes the circuit.
 */

struct ALU_unit {
    // Input lines
    char a, b;
    // Output lines
    char output;
    char carry_out;
};

struct ALU {
    // Input parallel lines
    char inva;
    char ena, enb;
    char f0, f1;
    char inc;
    // ALU units description
    struct ALU_unit *unit;
    unsigned short n_units;
};

struct ALU *alu_create(unsigned short units);
void alu_free(struct ALU *alu);
int alu_process(struct ALU *alu);

// Helpers
char alu_overflow(struct ALU *alu);
void alu_set_line(struct ALU *alu, char ab, char *line);
void alu_get_line(struct ALU *alu, char *line);
