#include "microcode.h"

struct microcode *microcode_create(int n_cmds)
{
  struct microcode *mcode = (struct microcode *)malloc(sizeof(struct microcode));
  if (!mcode)
    ERR("Can't allocate memory for microcode");
  mcode->cmd = (struct mir *)calloc(n_cmds, sizeof(struct mir));
  if (!mcode->cmd)
    ERR("Can't allocate memory for %d commands in microcode", n_cmds);
  
  mcode->n_cmds = n_cmds;
  return mcode;
}

void microcode_free(struct microcode *mcode)
{
  free(mcode->cmd);
  free(mcode);
}

struct mir *process_cmd(struct microcode *mcode, struct mir *cmd)
{
  return mcode->cmd + cmd->next_address/sizeof(struct mir);
}
