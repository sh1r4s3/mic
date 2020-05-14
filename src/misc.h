#include <stdio.h>

// Emit log message
#define ERR(format, ...) \
    { \
      fprintf(stderr, __FILE__ ":%d / " format "\n", __LINE__, ##__VA_ARGS__); \
      exit(-1); \
    }
