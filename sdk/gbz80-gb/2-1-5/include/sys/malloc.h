/*
  sys/malloc.h

  Header for a simple implementation of malloc()
*/
#ifndef MALLOC_INCLUDE
#define MALLOC_INCLUDE

#include <types.h>

#if 1
#define MALLOC_DEBUG(fun, msg)
#else
#define MALLOC_DEBUG(fun, msg) printf("%s: %s\n", fun, msg);
#endif

#endif	/* __SYS_MALLOC_H */
