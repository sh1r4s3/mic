#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "misc.h"
#include "mir.h"

struct microcode
{
    struct mir *cmd;
    int n_cmds;
};

struct microcode *microcode_create(int n_cmds);
void microcode_free(struct microcode *mcode);
struct microcode *microcode_load(const char *fname);
struct mir *process_cmd(struct microcode *mcode, struct mir *cmd);
