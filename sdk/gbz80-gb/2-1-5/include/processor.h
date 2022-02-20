/*
  processor.h

  Various processor related defines
*/

#ifndef __PROCESSOR_H
#define __PROCESSOR_H

#ifdef GAMEBOY
/* Disables the fallback C malloc */
#undef	PROVIDES_MALLOC
#undef	PROVIDES_FREE
#undef	PROVIDES_REALLOC
#undef	PROVIDES_CALLOC
#undef  PROVIDES_MALLOC_FIND
#endif /* GAMEBOY */
#endif /* __PROCESSOR_H */
