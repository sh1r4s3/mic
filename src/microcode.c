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

struct microcode *microcode_load(const char *fname)
{
  struct stat s;
  int fd = open(fname, O_RDONLY);
  if (fd < 0)
    ERR("Can't open file %s / errno=%d / %s", fname, errno, strerror(errno));

  if (fstat(fd, &s) < 0)
    ERR("Can't get size of the file %s / errno=%d / %s", fname, errno, strerror(errno));

  // Basic check
  if (s.st_size % sizeof(struct mir))
    ERR("It is seems that the file is corrupted");

  int cmds = s.st_size/sizeof(struct mir);
  struct microcode *mcode = microcode_create(cmds);
  ssize_t sz = read(fd, mcode, sizeof(struct mir)*cmds);
  if (sz != sizeof(struct mir)*cmds)
    ERR("Can't read microcode from the file (read %li)", sz);

  close(fd);
}

struct mir *process_cmd(struct microcode *mcode, struct mir *cmd)
{
  return mcode->cmd + cmd->next_address/sizeof(struct mir);
}
