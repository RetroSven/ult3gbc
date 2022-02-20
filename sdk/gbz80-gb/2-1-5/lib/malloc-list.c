/*
  malloc.c

  Simple implementation of a malloc library for the GB

  Notes:
  * Designed for the Nintendo GB - 8 bitter with little RAM, so efficency and allocation
  speed are important.  recursion or malloc/free pairs are rare.
  * Garbage collection is lazy
  * Singly linked list of 'hunks' - regions of memory
  * Each hunk is preceeded by a header - header describes a singly linked list
  * If the header is corrupted, this system dies - but so does the program so youve got other problems
  * All allocations are on byte boundries
  * See types.h for the definitions of UBYTE, BYTE...
  * Theres a bug in GBDK 2.0b9 - cant handle pointer addition, requiring (UWORD) casting
*/
#include "config.h"
#if USE_LIST_BASED_MALLOC

#include "sys/malloc.h"
#include "processor.h"
#include "platform.h"
#include <types.h>
#include <stdio.h>

#define FREE_FLAG 0x8000U
#define SIZE_MASK 0x7FFFU

#define BLOCK_OVERHEAD sizeof(UWORD)

extern UWORD malloc_heap_start[];
void malloc_dump(void);

/*
  malloc_init

  Initialise the malloc system.  
  Only initalises if the magic number on the first hunk is invalid.
  Note that this number is invalidated in crt0.s 
  
  Returns: BYTE, -1 on failure, 0 on success
*/
BYTE malloc_init(void)
{
    UWORD *p;
    if (!*malloc_heap_start) {
	/* Init by setting up the first hunk */

	MALLOC_DEBUG("malloc_init", "Setting up");

	/* Set the size to all of free memory (mem ends at 0xE000), less 200h for the stack */
	*malloc_heap_start = (MALLOC_HEAP_END - BLOCK_OVERHEAD - (UWORD)malloc_heap_start) | FREE_FLAG;
	p = (UWORD *)((UBYTE *)malloc_heap_start + BLOCK_OVERHEAD + (*malloc_heap_start & SIZE_MASK));
	*p = 0;
	return 0;
    }
    return -1;
}

/*
  malloc_gc

  Do a grabage collect on the malloc list.  Join any adjacent, free hunks into one
  free hunk.  Called by malloc() when there is no one free block of memory big
  enough.
  Note that malloc_gc is only called when needed to save processor time
  Note:  assumes that hunks ae consecutive
*/
void malloc_gc(void)
{
    /* Note: Hunks are consecutive */
    /* thisHunk is the one that were lookin at */
    /* nextHunk is used when joining hunks */
    UWORD *pThis, *pNext;

    /* changed is set if at least two hunks are joined */
    /* Note that logically all will be joined on the first pass, but you get that */
    INT8 fDidSomething;
    
    MALLOC_DEBUG("malloc_gc","Running");
    malloc_dump();
    do {
	pThis = malloc_heap_start;
	fDidSomething = FALSE;
	/* Walk the whole of the linked list */
	while (*pThis) {
	    /* Is this hunk free ? */
	    if ((WORD)*pThis < 0) {
		/* Yes - if the next is as well, join them */
		pNext = (UWORD *)((UBYTE *)pThis + (*pThis & SIZE_MASK) + BLOCK_OVERHEAD);
		/* This catches the case where there are many consecutive free hunks */
		while ((WORD)*pNext < 0) {
		    /* Must be consecutive */
		    /* Dont worry about wrap around on the top bit here - fix it later */
		    fDidSomething = TRUE;
		    *pThis += *pNext & SIZE_MASK + BLOCK_OVERHEAD;
		    pNext = (UWORD *)((UBYTE *)pNext + (*pNext & SIZE_MASK) + BLOCK_OVERHEAD);
		}
	    }
	    pThis = (UWORD *)((UBYTE *)pThis + (*pThis & SIZE_MASK) + BLOCK_OVERHEAD);
	}
	/* If thisHunk is not NULL, then the magic number was corrupt */
    } while (fDidSomething);
    malloc_dump();
}

#ifndef PROVIDES_MALLOC	
/*
  malloc

  Attempt to allocate a hunk of at least 'size' bytes from free memory
  Return:  pointer to the base of free memory on success, NULL if no memory
  was available
*/
void *malloc( UWORD size )
{
    /* thisHunk: list walker
     */
    UWORD *pThis, *pNew;

    UBYTE firstTry;
    
    firstTry = 1;	/* Allows gc if no big enough hunk is found */

    printf("malloc() on %lu\n", size);

    /* Dont allocate blocks of zero size */
    size = size ? size : 1;

    //    malloc_dump();
    do {
	pThis = malloc_heap_start;
	/* Walk the list */
	while (*pThis) {
	    if ((WORD)*pThis < 0) {
		MALLOC_DEBUG("malloc", "Found free hunk" );
		
		/* Free, is it big enough? (dont forget the size of the header) */
		if ((*pThis & SIZE_MASK) >= (size+BLOCK_OVERHEAD)) {
		    MALLOC_DEBUG("malloc","Found a big enough hunk.");
		    
		    /* Yes, big enough */
		    /* Create a new header at the end of this block */
		    /* Note: the header can be of zero length - should add code to combine */
		    /* Shrink this hunk, and mark it as used */
		    /* size is the free space, less that allocated, less the new header */
		    pNew = (UWORD *)(((UBYTE *)pThis) + size + BLOCK_OVERHEAD);
		    *pNew = *pThis - size - BLOCK_OVERHEAD;

		    *pThis = size&SIZE_MASK;

		    /* Return a pointer to the new region */
		    return (void *)((UBYTE *)pThis + BLOCK_OVERHEAD);
		}
	    }
	    /* Advance */
	    pThis = (UWORD *)((UBYTE *)pThis + (*pThis&SIZE_MASK) + BLOCK_OVERHEAD);
	}
	/* Try again after a garbage collect */
	malloc_gc();
    } while (firstTry--);

    /* Couldnt do it */
    return NULL;
}
#endif /* PROVIDES_MALLOC */

void malloc_dump(void) 
{
    /* Walk the malloc list */
    UWORD *pWalk;
    pWalk = malloc_heap_start;
    
    while (*pWalk) {
	if ((WORD)*pWalk < 0) {
	    printf("Free");
	}
	else {
	    printf("Used");
	}
	printf(" hunk at %lx, length %ld\n", (UWORD)pWalk, (UWORD)(*pWalk & SIZE_MASK));
	pWalk = (UWORD *)((UBYTE *)pWalk + (*pWalk & SIZE_MASK) + BLOCK_OVERHEAD);
    }
    if (pWalk != (UWORD *)MALLOC_HEAP_END) {
	printf("malloc_dump: somethings stuffed (%lx).\n", (UWORD)pWalk);
    }
    printf("Done at %lx.\n", (UWORD)pWalk);
}

#ifndef PROVIDES_REALLOC
void *realloc( void *current, UWORD size )
{
    /* Cant be bothered re-implementing this */
    UBYTE *pRet;
    pRet = (UBYTE *)malloc(size);
    if (pRet) {
	memcpy((UBYTE *)current, pRet, size);
	free(current);
    }
    return pRet;
}
#endif /* PROVIDES_REALLOC */

#ifndef PROVIDES_CALLOC
void *calloc( UWORD nmem, UWORD size )
{
    void *malloced;

    malloced = (UBYTE *)malloc( nmem*size );
    if (malloced!=NULL) {
	memset( malloced, 0, nmem*size );
	return malloced;
    }
    return	NULL;
}
#endif

#ifndef PROVIDES_FREE
/*
  free

  Attempts to free the memory pointed to by 'ptr'
  Different from the standard free:  returns -1 if already free, or -2 if not part of the malloc list
*/
BYTE free(void *ptr)
{
    /* Do a relativly safe free by only freeing vaild used hunks */
    UWORD *pThis, *pLast, *pNext;

    pThis = malloc_heap_start;
    pLast = NULL;
    
    /* Adjust the pointer to point to the start of the hunk header - makes the comparision easier */
    ptr = (void *)((UBYTE *)ptr - BLOCK_OVERHEAD);
    
    /* Walk the linked list */
    while (*pThis) {
	/* Is this the hunk? */
	if (pThis == ptr) {
	    MALLOC_DEBUG("free", "Found hunk");
	    /* Only free it if it's used */
	    if (*pThis > 0) {
		/* Check the next hunk as well - see if we can combine */
		pNext = (UWORD *)((UBYTE *)pThis + *pThis + BLOCK_OVERHEAD);
		if (*pNext & FREE_FLAG) {
		    *pThis += BLOCK_OVERHEAD + (*pNext & SIZE_MASK);
		}
		if (pLast) {
		    if (*pLast & FREE_FLAG) {
			*pLast += BLOCK_OVERHEAD + *pThis;
			*pLast |= FREE_FLAG;
		    }
		    else {
			*pThis |= FREE_FLAG;
		    }
		}
		else {
		    *pThis |= FREE_FLAG;
		}
		return 0;
	    }
	    MALLOC_DEBUG("free", "Attempt to free a free hunk");
	    return -1;
	}
	/* walking... */
	pLast = pThis;
	pThis = (UWORD *)((UBYTE *)pThis + (*pThis & SIZE_MASK) + BLOCK_OVERHEAD);
    }
    MALLOC_DEBUG("free", "No hunk found");
    return -2;
}
#endif /* PROVIDES_FREE */
#endif /* USE_LIST_BASED_MALLOC */
